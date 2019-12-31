#pragma once
#include "Vertex.h"

bool doubleEqual(double a, double b);

double distance(const Vertex& v1, const Vertex& v2);
bool sameX(const Vertex& v1, const Vertex& v2);
bool sameY(const Vertex& v1, const Vertex& v2);
bool operator<(const Vertex& lhs, const Vertex& rhs);
