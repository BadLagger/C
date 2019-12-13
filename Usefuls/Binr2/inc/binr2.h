#ifndef BINR2_H
#define BINR2_H

//! \brief Максимальная длинна внутренних буферов в байтах
#define MAX_INTERNAL_BUFFER 256*7
//! \brief Максимальное значение поля длины пакета
#define BINR2_MAX_DATA_SIZE 2047

//! \brief Список ошибок распаковщика
typedef enum{
	Binr2DecodeError_NoStartFrame = 0,  //!< отсутствует начало пакета
	Binr2DecoderError_NoSoF_2,          //!< второй байт преамбулы неправильный
	Binr2DecoderError_NoSoF_3,          //!< третий байт преамбулы неправильный
	Binr2DecoderError_NoSoF_4,          //!< четвёртый байт преамбулы неправильный
	Binr2DecoderError_LenFrame,            //!< превышено значение поля длины
	Binr2DecoderError_InternalBufferError, //!< входной буфер слишком мал для приёма такого пакета
	Binr2DecoderError_CRC,                 //!< ошибка CRC 
	Binr2DecodeError_UnknownState,         //!< неизвестное состояние распаковщика
	Binr2DecodeError_NoError               //!< ошибок не обнаружено
}Binr2DecodeErrors;

//! \brief Список ошибок упаковщика
typedef enum{
	Binr2EncodeError_ImpossibleId = 0,    //!< недопустимый идентификатор пакета
	Binr2EncodeError_InternalBufferError, //!< внутрений буфер слишком мал для такого количества данных
	Binr2EncodeError_ExternalBufferError, //!< внешний буфер слишком мал 
	Binr2EncodeError_NoError              //!< ошибок не обнаружено
}Binr2EncodeErrors;

//! \brief Список состояний распаковщика
typedef enum{
	Binr2DecodeState_SeekStartOfFrame = 0,  //!< поиск начала пакета
	Binr2DecodeState_WaitSoF_2,             //!< ожидание второго байта преамбулы
	Binr2DecodeState_WaitSoF_3,             //!< ожидание третьего байта преамбулы
	Binr2DecodeState_WaitSoF_4,             //!< ожидание четвёртого байта преамбулы
	Binr2DecodeState_WaitLength_1,          //!< ожидание первого байта длинны
	Binr2DecodeState_WaitLength_2,          //!< ожидание второго байта длинны
	Binr2DecodeState_GetData,               //!< получение поля данных
	Binr2DecodeState_WaitCRC_1,             //!< получение первого байта CRC
	Binr2DecodeState_WaitCRC_2,             //!< получение второго байта CRC
	Binr2DecodeState_MaxState
}Binr2DecodeStates;

//! \brief   Управляющая структура BINR2
//! \remark  Благодаря этой структуре проект может содержать несколько обработчиков BINR2 и использовать их в разных потоках. Но этот подход несёт накладные расходы по использованию стека
//! \warning Вне модуля BINR2 не должно быть прямых обращений к этой структуре. Для всех манипуляций с данными необходимо использовать интерфейс модуля.
typedef struct{
	unsigned char  decoderBuffer[MAX_INTERNAL_BUFFER]; //!< буфер для хранения входящих данных
	unsigned char  decoderData[MAX_INTERNAL_BUFFER];   //!< буфер для хранения разобранных данных
	unsigned short decoderBufferLen;                   //!< количество байт во входящем буфере
	unsigned short decoderDataLen;                     //!< количество байт в буфере разобраных данных
	unsigned short decoderWaitLen;                     //!< количество ожидаемых данных
	unsigned short decoderCrc;                         //!< CRC пакета распаковки
	unsigned short decoderCurrentCrc;                  //!< фактическая CRC
	unsigned char  decoderId;                          //!< идентификатор последнего разобранного пакета
	Binr2DecodeErrors   decoderErr;                         //!< код ошибки разборщика 
	Binr2DecodeStates   decoderState;                       //!< состояние распаковщика
		
	unsigned char  encodeData[MAX_INTERNAL_BUFFER]; //!< буфер данных для упаковки
	unsigned short encodeDataLen;                   //!< количество байт в буфере даннных для упаковки 
	unsigned char  encodeId;                        //!< идентифкатор для упаковки
	Binr2EncodeErrors   encodeErr;                       //!< код ошибки упаковщика (формирователя)
}BINR2, *BINR2ptr;

//! \brief Перечисление возможых результатов работы распаковщика  
typedef enum{
	Binr2Result_Idle = 0,
	Binr2Result_Ok,
	Binr2Result_Max
}Binr2Results;

/*!
 * \brief     Инициализация управляющей структуры обработчика BINR2
 * \param[in] указатель на управляющую структуру
 *****************************************************************************/
extern void binr2_init(BINR2ptr ctrl);
/*!
 *  \brief     Распаковщик входящих данных
 *  \param[in] байт из входящего потока
 *  \return    true - пакет разобран, false - пакет не обнаружен
 *****************************************************************************/
extern Binr2Results binr2_decode(BINR2ptr ctrl, unsigned char const byte);
/*!
 *  \brief     Получение последнего разобраного пакета
 *  \param[in] указатель на управляющую структуру
 *  \return    идентификатор пакета (0х00 - 0хFF)
 *****************************************************************************/
extern unsigned char binr2_getDecodePkgId(BINR2ptr ctrl);
/*!
 *  \brief      Получение данных из последнего разобранного пакета
 *  \param[in]  указатель на управляющую структуру
 *  \param[out] указатель на буфер в который будут выгружены данные
 *  \param[in]  размер внешнего буфера в байтах
 *  \return     количество данных выгруженных во внешний буфер
 *****************************************************************************/
extern unsigned short binr2_getDecodeData(BINR2ptr ctrl, unsigned char *out, unsigned short const size);
/*!
 *  \brief      Получение значения из поля длинны данных пакета
 *  \param[in]  указатель на управляющую структуру
 *  \return     значение поля длинны последнего пакета
 *****************************************************************************/
extern unsigned short binr2_getDecodeDataSizeField(BINR2ptr ctrl);
/*!
 *  \brief     Получение кода последней возникшей ошибки при разборе
 *  \param[in] указатель на управляющую структуру
 *  \return    код ошибки \ref DecodeErrors
 *****************************************************************************/
extern Binr2DecodeErrors binr2_getDecodeError(BINR2ptr ctrl);
/*!
 *  \brief     Сброс флага ошибок распаковщика
 *  \param[in] указатель на управляющую структуру
 *****************************************************************************/
extern void     binr2_resetDecodeError(BINR2ptr ctrl);
/*!
 *  \brief      Упаковщик (генератор) исходящих пакетов
 *  \param[in]  указатель на управляющую структуру
 *  \param[out] ссылка на буфер в котором будет сформирован пакет
 *  \param[in]  максимальный размер исходящего буфера в байтах
 *  \return     размер сформированного пакета в исходящем буфере
 *****************************************************************************/
extern unsigned short binr2_encode(BINR2ptr ctrl, unsigned char *out, unsigned short const size);
/*!
 *  \brief     Установка идентификатора пакета для формирования
 *  \param[in] указатель на управляющую структуру
 *  \param[in] идентификатор пакета который будет сформирован (00 - FF)
 *********************************************************************/
extern void binr2_setEncodePkgId(BINR2ptr ctrl, unsigned char const id);
/*!
 *  \brief     Установка данных которые будут добавлены в следующий пакет
 *  \param[in] указатель на управляющую структуру
 *  \param[in] ссылка на буфер с данными
 *  \param[in] размер данных в байтах
 *********************************************************************/
extern void binr2_setEncodeData(BINR2ptr ctrl, unsigned char *in, unsigned short const size);
/*!
 *  \brief     Получение кода ошибки возникшей при формировании пакета
 *  \param[in] указатель на управляющую структуру
 *  \return    код ошибки \ref EncodeErrors
 *********************************************************************/
extern Binr2EncodeErrors binr2_getEncodeError(BINR2ptr ctrl);
/*!
 *  \brief     Сброс флага ошибок упаковщика 
 *  \param[in] указатель на управляющую структуру
 *********************************************************************/
extern void resetEncodeError(BINR2ptr ctrl);

#endif