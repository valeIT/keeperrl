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

#include "collective_control.h"
#include "enum_variant.h"
#include "entity_set.h"
#include "village_behaviour.h"
#include "event_listener.h"

class Task;

class VillageControl : public CollectiveControl, public EventListener<VillageControl> {
  public:
  static PVillageControl create(WCollective col, optional<VillageBehaviour> v);

  void onEvent(const GameEvent&);

  private:
  struct Private {};

  public:
  VillageControl(Private, WCollective, optional<VillageBehaviour>);

  protected:
  virtual void update(bool currentlyActive) override;
  virtual void onMemberKilled(WConstCreature victim, WConstCreature killer) override;
  virtual void onOtherKilled(WConstCreature victim, WConstCreature killer) override;
  virtual void onRansomPaid() override;
  virtual vector<TriggerInfo> getTriggers(WConstCollective against) const override;

  SERIALIZATION_DECL(VillageControl);

  private:
  friend class VillageBehaviour;
  void launchAttack(vector<WCreature> attackers);
  void considerWelcomeMessage();
  void considerCancellingAttack();
  void checkEntries();
  bool isEnemy(WConstCreature);
  WCollective getEnemyCollective() const;
  bool canPerformAttack(bool currentlyActive);
  void acceptImmigration();

  optional<VillageBehaviour> SERIAL(villain);

  double SERIAL(victims) = 0;
  EntitySet<Item> SERIAL(myItems);
  int SERIAL(stolenItemCount) = 0;
  map<TeamId, int> SERIAL(attackSizes);
  bool SERIAL(entries) = false;
  double SERIAL(maxEnemyPower) = 0;
};

