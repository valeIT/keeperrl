#pragma once

#include "util.h"

struct TestStruct1 {
  int SERIAL(x);
  int SERIAL(y);
  SERIALIZE_ALL(NAMED(x), NAMED(y))
  bool operator == (const TestStruct1& o) const {
    return x == o.x && y == o.y;
  }
};

struct TestStruct2 {
  optional<TestStruct1> SERIAL(s);
  int SERIAL(v);
  vector<int> SERIAL(w);
  SERIALIZE_ALL(NAMED(s), NAMED(v), OPTION(w))
  bool operator == (const TestStruct2& o) const {
    return s == o.s && v == o.v && w == o.w;
  }
};

struct TestStruct3 {
  optional<TestStruct2> SERIAL(a);
  SERIALIZE_ALL(NAMED(a))
  bool operator == (const TestStruct3& o) const {
    return a == o.a;
  }
};

struct TestStruct4 {
  int SERIAL(x) = 1;
  int SERIAL(y) = 2;
  SERIALIZE_ALL(OPTION(x), OPTION(y))
  bool operator == (const TestStruct4& o) const {
    return x == o.x && y == o.y;
  }
};

struct TestStruct5 {
  TestStruct4 SERIAL(a);
  SERIALIZE_ALL(NAMED(a))
  bool operator == (const TestStruct5& o) const {
    return a == o.a;
  }
};
