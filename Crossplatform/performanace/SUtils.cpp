//!
//! Вывод отладочной информации
//!

#include "SUtils.h"

SUtils::Logger::Dumper<1, SUtils::Logger::destination> d1cout;
SUtils::Logger::Dumper<2, SUtils::Logger::destination> d2cout;
SUtils::Logger::Dumper<3, SUtils::Logger::destination> d3cout;
