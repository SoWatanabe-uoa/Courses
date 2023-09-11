CREATE SCHEMA `dialogue_creator` ;

CREATE TABLE `dialogue_creator`.`curator` (
  `curator_id` VARCHAR(45) NOT NULL,
  `password` VARCHAR(45) NOT NULL,
  UNIQUE INDEX `curator_id_UNIQUE` (`curator_id` ASC));

CREATE TABLE `dialogue_creator`.`coverpage` (
  `coverpage_id` INT NOT NULL AUTO_INCREMENT,
  `image_url` VARCHAR(300) NULL,
  PRIMARY KEY (`coverpage_id`));

CREATE TABLE `dialogue_creator`.`light_bulb` (
  `coverpage_id` INT NOT NULL,
  `painting_id` INT NOT NULL,
  `_top` INT NULL,
  `_left` INT NULL);

CREATE TABLE `dialogue_creator`.`painting` (
  `painting_id` INT NOT NULL,
  `image_url` VARCHAR(300) NULL,
  `title` VARCHAR(45) NULL,
  `explanation` VARCHAR(300) NULL,
  PRIMARY KEY (`painting_id`));


CREATE TABLE `dialogue_creator`.`wordballoon` (
  `painting_id` INT NOT NULL,
  `size` INT NULL,
  `pre_description` VARCHAR(45) NULL,
  `_top` INT NULL,
  `_left` INT NULL,
  `flipped` TINYINT NULL);

CREATE TABLE `dialogue_creator`.`dialogue` (
  `painting_id` INT NOT NULL,
  `image_url` VARCHAR(300) NULL);
