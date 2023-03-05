#include "project1/a.h"
#include "project2/b.h"
#include <stdio.h>

b_class::b_class(){}

void b_class::process() {
	a_class a = a_class();
	a.process();
}