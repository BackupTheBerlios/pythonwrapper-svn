
%module TestSwig
%{
#include "TSClassA.h"
#include "TSClassB.h"
#include "TSInner.h"
#define PW_Embedded
%}

#define TS_EXPORT

%include PWEmbedded.i

%include TSClassA.h
%include TSClassB.h
%include TSInner.h
