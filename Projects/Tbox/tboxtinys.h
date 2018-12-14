#ifndef TBOXTINYS_H_INCLUDED
#define TBOXTINYS_H_INCLUDED

#ifdef __cplusplus
#define C_CPP "C"
#else
#define C_CPP
#endif

extern C_CPP void CreateNewTiny(int x, int y);
extern C_CPP int  GetTinysNumber(void);
extern C_CPP int  CheckTinyPos(int x, int y);
extern C_CPP void DestroyTinyById(int id);

#endif // TBOXTINYS_H_INCLUDED
