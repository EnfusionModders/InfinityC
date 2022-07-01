/* date = July 1st 2022 5:26 pm */

#ifndef CONVENTIONS_H
#define CONVENTIONS_H

// we define OS dependent conventions used throughout the app here

#if defined(_WIN64)
#define fastcall __fastcall
#else
#define fastcall __attribute__((fastcall))
#endif

#endif //CONVENTIONS_H
