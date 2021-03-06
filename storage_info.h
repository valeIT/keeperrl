#pragma once

#include "util.h"

struct StorageInfo {
  StorageId SERIAL(storage);
  Collective* SERIAL(collective) = nullptr;
  SERIALIZE_ALL(storage, collective);
};
