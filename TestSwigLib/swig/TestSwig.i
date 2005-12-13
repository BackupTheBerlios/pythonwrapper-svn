
%module TestSwig
%{
#include "TSClassA.h"
#include "TSClassB.h"
#include "TSInner.h"
%}

#define TS_EXPORT

%include TSClassA.h
%include TSClassB.h
%include TSInner.h
