#include "project1/a.h"
#include "project2/b.h"
#include <stdio.h>
#include <pybind11/pybind11.h>

b_class::b_class(){}

void b_class::process() {
	a_class a = a_class();
	a.process();
}

namespace py = pybind11;

PYBIND11_MODULE(project2, m) {
	py::class_<b_class>(m, "b_class")
		.def(py::init<>());
}
