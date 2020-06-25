#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

Player::Player(MainPlayerData playerData, size_t id) :
  LiveEntity(playerData.position, playerData.points, playerData.skills, 
  playerData.level),
  id(id),
  nick(playerData.nick),
  gold(playerData.gold),
  experience(playerData.experience),
  rootd(playerData.rootd),
  inventory(playerData.inventory),
  movement(playerData.movement),
  equipment(playerData.equipment) {
    setRighHandSkills(rightSkills, equipment.rightHand);
    setLeftHandSkills(leftSkills, equipment.leftHand);
    setBodySkills(bodySkills, equipment.body);
    setHeadSkills(headSkills, equipment.head);
}

std::unique_ptr<Player> Player::createPlayer(size_t id, std::string nick, 
  PlayerRootData root) {
    Equations equations;
    MainPlayerData data;
  
    data.rootd = root;
    data.nick = nick;
    data.gold = 0;
    data.level = 1;

    int width = 25, height = 48;

    Player::setClassSkills(data.skills, data.rootd);
    Player::setRaceSkills(data.skills, data.rootd);

    data.experience.maxLevelExperience = 
      equations.maxLevelExperience(data.level);
    data.experience.currentExperience = 0;
    
    data.inventory.helmet = "";
    
    data.position = {100 , 100, width, height};
    data.points.totalHP = equations.maxLife(data.skills.classConstitution, 
      data.skills.classHealth, data.skills.raceHealth, 
      data.level);
    data.points.currentHP = data.points.totalHP;
    
    data.points.totalMP = equations.maxMana
      (data.skills.inteligence, data.skills.classMana, data.skills.raceMana, 
      data.level);
    data.points.currentMP = data.points.totalMP;

    Player::setInitEquipment(data.equipment, data.rootd);

    data.movement.xDir = 0;
    data.movement.yDir = 0;

    std::unique_ptr<Player> player(new Player(data, id));

    return player;
}

void Player::setClassSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.pclass){
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

void Player::setRaceSkills(SkillsData &skills, PlayerRootData &root){
  switch (root.prace){
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
    default:
      break;
  }
}

void Player::setInitEquipment(EquipmentData &equipment, PlayerRootData &root){
  equipment.body = TUNIC;
  equipment.head = HELMET;
  equipment.leftHand = SHIELD;    
  equipment.rightHand = SWORD;
}


void Player::setRighHandSkills(RightHandEquipmentSkills
  &rightSkills, RightHandEquipment &rightEquipment){
    switch (rightEquipment)
    {
    case SWORD:
      rightSkills.maxDamage = SWORD_MAX_DAMAGE;
      rightSkills.minDamage = SWORD_MIN_DAMAGE;
      break;
    default:
      break;
    }
}

void Player::setLeftHandSkills(LeftHandEquipmentSkills
  &leftSkills, LeftHandEquipment &leftEquipment){
    switch (leftEquipment)
    {
    case SHIELD:
      leftSkills.maxDefense = IRON_SHIELD_MAX_DEFENSE;
      leftSkills.minDefense = IRON_SHIELD_MIN_DEFENSE;
      break;
    default:
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
      break;
    }
}

int Player::attack(LiveEntity &entity, int xCoord, int yCoord){
  PositionData attackZoneData = {
    xCoord,
    yCoord,
    ATTACK_ZONE_WIDTH,
    ATTACK_ZONE_HEIGHT};
  Entity attackZone(attackZoneData);
  
  bool canAttack = entity.checkCollision(attackZone);
  
  if (!canAttack) return 0;

  bool dodged = gameEquations.dodgeAttack(LiveEntity::skills.agility);

  if (dodged) return 0;

  int damage = gameEquations.damage(skills.strength, rightSkills);

  return damage;
}

void Player::addExperience(int &damage, size_t &otherLevel, int &otherHealth, 
  int &otherMaxHEalth){
    if (otherHealth <= 0){
      experience.currentExperience -= gameEquations.killExperience(
        otherMaxHEalth, otherLevel, level);
      return;
    }
    experience.currentExperience += gameEquations.attackExperience(
      damage, otherLevel, level);
}

void Player::rcvDamage(int &damage){
  int defensePoints = defend();
  health.currentHP -= (damage - defensePoints);
  std::cout << "Defense points: " << defensePoints << std::endl;
  std::cout << "Puntos de vida restantes: " << health.currentHP << std::endl;
}

int Player::defend(){
  return gameEquations.defend(skills.agility, bodySkills, 
    leftSkills, headSkills);
}



Player::~Player(){}
