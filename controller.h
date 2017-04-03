/* Copyright (C) 2013-2014 Michal Brzozowski (rusolis@poczta.fm)

   This file is part of KeeperRL.

   KeeperRL is free software; you can redistribute it and/or modify it under the terms of the
   GNU General Public License as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   KeeperRL is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along with this program.
   If not, see http://www.gnu.org/licenses/ . */

#pragma once

#include "enums.h"
#include "util.h"

class Creature;
class MapMemory;
class Item;
class Level;
class PlayerMessage;

class Controller : public OwnedObject<Controller> {
  public:
  Controller(WCreature);
  Controller(const Controller&) = delete;
  Controller(Controller&&) = delete;

  virtual bool isPlayer() const = 0;

  virtual void you(MsgType type, const string& param) = 0;
  virtual void you(MsgType type, const vector<string>& param) = 0;
  virtual void you(const string& param) = 0;
  virtual void privateMessage(const PlayerMessage& message) {}

  virtual void onKilled(WConstCreature attacker) {}
  virtual void onItemsGiven(vector<WItem> items, WCreature from) { }
  virtual void onDisplaced() {}

  virtual void makeMove() = 0;
  virtual void sleeping() {}
  virtual bool isCustomController() { return false; }

  virtual void onBump(WCreature) = 0;

  virtual ~Controller() {}

  SERIALIZATION_DECL(Controller);

  protected:
  WCreature getCreature() const;

  private:
  WCreature SERIAL(creature);
};

class DoNothingController : public Controller {
  public:
  DoNothingController(WCreature);

  virtual bool isPlayer() const override;
  virtual void you(MsgType type, const string& param) override;
  virtual void you(MsgType type, const vector<string>& param) override;
  virtual void you(const string& param) override;
  virtual void makeMove() override;
  virtual void onBump(WCreature) override;

  protected:
  SERIALIZATION_DECL(DoNothingController);
};

class ControllerFactory {
  public:
  ControllerFactory(function<PController(WCreature)>);
  PController get(WCreature) const;

  private:
  function<PController(WCreature)> fun;
};

