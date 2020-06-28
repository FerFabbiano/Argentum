#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

Player::Player(MainPlayerData playerData, size_t id):
  LiveEntity(playerData.position, playerData.points, playerData.skills, 
  playerData.level),
  id(id),
  nick(playerData.nick),
  gold(playerData.gold),
  experience(playerData.experience),
  rootd(playerData.rootd),
  inventory(playerData.inventory),
  movement(playerData.movement),
  equipment(playerData.equipment){
    setRighHandSkills(rightSkills, equipment.rightHand);
    setLeftHandSkills(leftSkills, equipment.leftHand);
    setBodySkills(bodySkills, equipment.body);
    setHeadSkills(headSkills, equipment.head);
}

std::unique_ptr<Player> Player::createPlayer(size_t id, std::string nick, 
  PlayerRootData root) {
    MainPlayerData data;
  
    data.rootd = root;
    data.nick = nick;
    data.gold = 0;
    data.level = PLAYER_INITIAL_LEVEL;

    Player::setClassSkills(data.skills, data.rootd);
    Player::setRaceSkills(data.skills, data.rootd);

    Player::setDefaultEquipment(data);

    data.experience.maxLevelExperience = 0;
    data.experience.currentExperience = 0;
    Player::setExperienceData(data.level, data.experience);
        
    Player::setPositionData(root, data.position);

    data.points.totalHP = Equations::maxLife(data.skills.classConstitution, 
      data.skills.classHealth, data.skills.raceHealth, 
      data.level);
    data.points.currentHP = data.points.totalHP - 100;
    
    data.points.totalMP = Equations::maxMana
      (data.skills.inteligence, data.skills.classMana, data.skills.raceMana, 
      data.level);
    data.points.currentMP = data.points.totalMP - 50;

    data.movement.xDir = 0;
    data.movement.yDir = 0;

    std::unique_ptr<Player> player(new Player(data, id));

    return player;
}

void Player::setRaceSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.prace){
    case HUMAN:
      skills.classRecovery = HUMAN_RECOVERY;
      skills.classMana = HUMAN_MANA;
      skills.classMeditation = HUMAN_MEDITATION;
      skills.classHealth = HUMAN_HEALTH;
      skills.classConstitution = HUMAN_CONSTITUTION;
      skills.inteligence = HUMAN_INTELIGENCE;
      skills.strength = HUMAN_STRENGTH;
      skills.agility = HUMAN_AGILITY;
      break;
    case ELF:
      skills.classRecovery = ELF_RECOVERY;
      skills.classMana = ELF_MANA;
      skills.classMeditation = ELF_MEDITATION;
      skills.classHealth = ELF_HEALTH;
      skills.classConstitution = ELF_CONSTITUTION;
      skills.inteligence = ELF_INTELIGENCE;
      skills.strength = ELF_STRENGTH;
      skills.agility = ELF_AGILITY;
      break;
    case DWARF:
      skills.classRecovery = DWARF_RECOVERY;
      skills.classMana = DWARF_MANA;
      skills.classMeditation = DWARF_MEDITATION;
      skills.classHealth = DWARF_HEALTH;
      skills.classConstitution = DWARF_CONSTITUTION;
      skills.inteligence = DWARF_INTELIGENCE;
      skills.strength = DWARF_STRENGTH;
      skills.agility = DWARF_AGILITY;
      break;
    case GNOME:
      skills.classRecovery = GNOME_RECOVERY;
      skills.classMana = GNOME_MANA;
      skills.classMeditation = GNOME_MEDITATION;
      skills.classHealth = GNOME_HEALTH;
      skills.classConstitution = GNOME_CONSTITUTION;
      skills.inteligence = GNOME_INTELIGENCE;
      skills.strength = GNOME_STRENGTH;
      skills.agility = GNOME_AGILITY;
      break;
    default:
      break;
    }
}

void Player::setClassSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.pclass){
    case MAGE:
      skills.raceRecovery = MAGE_RECOVERY;
      skills.raceMana = MAGE_MANA;
      skills.raceMeditation = MAGE_MEDITATION;
      skills.raceHealth = MAGE_HEALTH;
      break;
    case CLERIC:
      skills.raceRecovery = CLERIC_RECOVERY;
      skills.raceMana = CLERIC_MANA;
      skills.raceMeditation = CLERIC_MEDITATION;
      skills.raceHealth = CLERIC_HEALTH;
      break;
    case PALADIN:
      skills.raceRecovery = PALADIN_RECOVERY;
      skills.raceMana = PALADIN_MANA;
      skills.raceMeditation = PALADIN_MEDITATION;
      skills.raceHealth = PALADIN_HEALTH;
      break;
    case WARRIOR:
      skills.raceRecovery = WARRIOR_RECOVERY;
      skills.raceMana = WARRIOR_MANA;
      skills.raceMeditation = WARRIOR_MEDITATION;
      skills.raceHealth = WARRIOR_HEALTH;
      break;
    default:
      break;
  }
}

/* VER SI TODAVIA SIRVE

void Player::setInitEquipment(EquipmentData &equipment, PlayerRootData &root){
  equipment.body = TUNIC;
  equipment.head = HELMET;
  equipment.leftHand = IRON_SHIELD;    
  equipment.rightHand = SIMPLE_BOW;
}

*/

void Player::setRighHandSkills(RightHandEquipmentSkills
  &rightSkills, RightHandEquipment &rightEquipment){
    switch (rightEquipment){
      case SWORD:
        rightSkills.maxDamage = SWORD_MAX_DAMAGE;
        rightSkills.minDamage = SWORD_MIN_DAMAGE;
        rightSkills.range = SWORD_RANGE;
        rightSkills.mana = 0;
        break;
      case SIMPLE_BOW:
        rightSkills.maxDamage = SIMPLE_BOW_MAX_DAMAGE;
        rightSkills.minDamage = SIMPLE_BOW_MIN_DAMAGE;
        rightSkills.range = SIMPLE_BOW_RANGE;
        rightSkills.mana = 0;
        break;
      case ASH_STICK:
        rightSkills.maxDamage = ASH_STICK_MAX_NDAMAGE;
        rightSkills.minDamage = ASH_STICK_MIN_DAMAGE;
        rightSkills.range = ASH_STICK_RANGE;
        rightSkills.mana = ASH_STICK_MANA;
      default:
        rightSkills.maxDamage = 0;
        rightSkills.minDamage = 0;
        rightSkills.range = 0;
        rightSkills.mana = 0;
        break;
    }
}

void Player::setLeftHandSkills(LeftHandEquipmentSkills
  &leftSkills, LeftHandEquipment &leftEquipment){
    switch (leftEquipment){
      case IRON_SHIELD:
        leftSkills.maxDefense = IRON_SHIELD_MAX_DEFENSE;
        leftSkills.minDefense = IRON_SHIELD_MIN_DEFENSE;
        break;
      default:
        leftSkills.maxDefense = 0;
        leftSkills.minDefense = 0;
        break;
    }
}

void Player::setBodySkills(BodyEquipmentSkills
  &bodySkills, BodyEquipment &bodyEquipment){
    switch (bodyEquipment)
    {
    case TUNIC:
      bodySkills.maxDefense = TUNIC_MAX_DEFENSE;
      bodySkills.minDefense = TUNIC_MIN_DEFENSE;
      break;
    default:
      bodySkills.maxDefense = 0;
      bodySkills.minDefense = 0;
      break;
    }
}

void Player::setHeadSkills(HeadEquipmentSkills
  &headSkills, HeadEquipment &headEquipment){
    switch (headEquipment)
    {
    case HELMET:
      headSkills.maxDefense = HELMET_MAX_DEFENSE;
      headSkills.minDefense = HELMET_MIN_DEFENSE;
      break;
    default:
      headSkills.maxDefense = 0;
      headSkills.minDefense = 0;
      break;
    }
}

void Player::setExperienceData(size_t &level, ExperienceData &experience){
    experience.minLevelExperience = experience.maxLevelExperience;
    experience.maxLevelExperience = 
      Equations::maxLevelExperience(level);
}

void Player::setPositionData(PlayerRootData &root, PositionData &position){
  position.w = PLAYER_WIDTH;
  position.h = PLAYER_HEIGHT;
  position.x = 2600;
  position.y = 2600;
}


bool Player::attack(LiveEntity &entity, int xCoord, int yCoord){
  PositionData attackZoneData = {
    xCoord - ATTACK_NPC_ZONE_WIDTH / 2,
    yCoord - ATTACK_ZONE_HEIGHT / 2,
    ATTACK_ZONE_WIDTH,
    ATTACK_ZONE_HEIGHT};
  Entity attackZone(attackZoneData);
  
  bool canAttack = entity.checkCollision(attackZone);
  if (!canAttack) return false;
  
  double distanceAttackZone =  Entity::getPositionDistance(
    attackZoneData , position);
  if (distanceAttackZone > rightSkills.range) return false;

  if (health.currentMP < rightSkills.mana) return false;

  health.currentMP -= rightSkills.mana;
  
  bool dodged = Equations::dodgeAttack(LiveEntity::skills.agility);
  if (dodged) return false;
  
  int damage = Equations::damage(skills.strength, rightSkills);
  entity.rcvDamage(damage);

  addExperience(damage, entity.level, entity.health.currentHP, 
    entity.health.totalHP);

  return true;
}

void Player::addExperience(int &damage, size_t &otherLevel, int &otherHealth, 
  int &otherMaxHEalth){
    if (otherHealth <= 0){
      experience.currentExperience += Equations::killExperience(
        otherMaxHEalth, otherLevel, level);
    }else {
      experience.currentExperience += Equations::attackExperience(
      damage, otherLevel, level);
    }

    if (experience.currentExperience >= experience.maxLevelExperience){
      level += 1;
      Player::setExperienceData(level, experience);

      health.totalHP = Equations::maxLife(skills.classConstitution, 
      skills.classHealth, skills.raceHealth, 
      level);
    
      health.totalMP = Equations::maxMana
      (skills.inteligence, skills.classMana, skills.raceMana, level);
    }
}

void Player::rcvDamage(int &damage){
  int defensePoints = defend();

  if (defensePoints > damage) return;
  
  health.currentHP -= (damage - defensePoints);

  if (health.currentHP < 0) health.currentHP = 0;
}

int Player::defend(){
  return Equations::defend(skills.agility, bodySkills, 
    leftSkills, headSkills);
}

void Player::setDefaultEquipment(MainPlayerData &data){
  InventoryElementData bodyArmour, weapon, healthPotion, manaPotion,
    weapon2;
  
  bodyArmour.amount = 1;
  bodyArmour.isEquiped = true;
  bodyArmour.equipableType = BODY_ARMOUR;
  bodyArmour.enumPosition = BodyEquipment::DEFAULT_B;
  data.equipment.body = DEFAULT_B;

  weapon.amount = 1;
  weapon.isEquiped = true;
  weapon.equipableType = WEAPON;
  weapon.enumPosition = RightHandEquipment::SWORD;
  data.equipment.rightHand = SWORD;

  /* Mano izquierda y cabeza quedan en default (nada equipado) */
  data.equipment.head = DEFAULT_H;
  data.equipment.leftHand = DEFAULT_L;

  healthPotion.amount = 2;
  healthPotion.isEquiped = false;
  healthPotion.equipableType = POTION;
  healthPotion.enumPosition = Potions::HEALTH;

  manaPotion.amount = 2;
  manaPotion.isEquiped = false;
  manaPotion.equipableType = POTION;
  manaPotion.enumPosition = Potions::MANA;

  weapon2.amount = 1;
  weapon2.isEquiped = false;
  weapon2.equipableType = WEAPON;
  weapon2.enumPosition = RightHandEquipment::SIMPLE_BOW;

  data.inventory.push_back(bodyArmour);
  data.inventory.push_back(weapon);
  data.inventory.push_back(healthPotion);
  data.inventory.push_back(manaPotion);
  data.inventory.push_back(weapon2);
}

void Player::equip(int inventoryPosition){
  Equipable type;
  RightHandEquipment right;
  LeftHandEquipment left;
  HeadEquipment head;
  BodyEquipment body;
  Potions potion;

  InventoryElementData& i = inventory[inventoryPosition];

  type = i.equipableType;

  switch (type) {
    case POTION: 
      potion = static_cast<Potions> (i.enumPosition);
      equip(potion, inventoryPosition);
      break;
    case WEAPON:
      right = static_cast<RightHandEquipment> (i.enumPosition);
      equip(right, inventoryPosition);
      break;
    case LEFT_HAND_DEFENSE:
      left = static_cast<LeftHandEquipment> (i.enumPosition);
      equip(left, inventoryPosition);
      break;
    case HEAD_DEFENSE: 
      head = static_cast<HeadEquipment> (i.enumPosition);
      equip(head, inventoryPosition);
      break;
    case BODY_ARMOUR:
      body = static_cast<BodyEquipment> (i.enumPosition);
      equip(body, inventoryPosition);
      break;
  }
}

void Player::equip(Potions potion, int inventoryPosition) {
  if (potion == HEALTH){
    health.currentHP = health.totalHP;
  }else if (potion == MANA){
    health.currentMP = health.totalMP;
  }

  inventory[inventoryPosition].amount -= 1;

  if (inventory[inventoryPosition].amount > 0) return;
  
  inventory.erase(inventory.begin() + inventoryPosition);
}

void Player::equip(RightHandEquipment rightHandEquipment, 
  int inventoryPosition) {
    inventory[inventoryPosition].isEquiped = true;
  
    equipment.rightHand = rightHandEquipment;
  
    Player::setRighHandSkills(rightSkills, rightHandEquipment);
  
    for (auto& it : inventory){
      if (it.equipableType != WEAPON) continue;
      it.isEquiped = false;
    }
}

void Player::equip(LeftHandEquipment leftHandEquipment, 
  int inventoryPosition) {
    inventory[inventoryPosition].isEquiped = true;
  
    equipment.leftHand = leftHandEquipment;
    
    Player::setLeftHandSkills(leftSkills, leftHandEquipment);
    
    for (auto& it : inventory){
      if (it.equipableType != LEFT_HAND_DEFENSE) continue;
      it.isEquiped = false;
    }
}

void Player::equip(HeadEquipment headEquipment, 
  int inventoryPosition) {
    inventory[inventoryPosition].isEquiped = true;
  
    equipment.head = headEquipment;
    
    Player::setHeadSkills(headSkills, headEquipment);
    
    for (auto& it : inventory){
      if (it.equipableType != HEAD_DEFENSE) continue;
      it.isEquiped = false;
    }
}

void Player::equip(BodyEquipment bodyEquipment, 
  int inventoryPosition) {
    inventory[inventoryPosition].isEquiped = true;
  
    equipment.body = bodyEquipment;
    
    Player::setBodySkills(bodySkills, bodyEquipment);
    
    for (auto& it : inventory){
      if (it.equipableType != BODY_ARMOUR) continue;
      it.isEquiped = false;
    }
}
