-- MySQL Script hand constructed

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema aoi_db
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `aoi_db` ;
CREATE SCHEMA IF NOT EXISTS `aoi_db` ;

USE `aoi_db` ;

-- -----------------------------------------------------
-- Table `aoi_db`.`user`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `aoi_db`.`user` ;

CREATE TABLE IF NOT EXISTS `aoi_db`.`user` (
  `user_id` INT NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(45) NOT NULL,
  `first_name` VARCHAR(45) NOT NULL,
  `last_name` VARCHAR(45) NOT NULL,
  `email` VARCHAR(100) NOT NULL,
  `phone` VARCHAR(45) NULL,
  `password` CHAR(64) NULL,     -- hashed SHA2 256
  PRIMARY KEY (`user_id`),
  UNIQUE INDEX `userID_UNIQUE` (`user_id` ASC),
  UNIQUE INDEX `username_UNIQUE` (`username` ASC))
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `aoi-db`.`alert`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `aoi_db`.`alert` ;

CREATE TABLE IF NOT EXISTS `aoi_db`.`alert` (
  `alert_id` INT NOT NULL AUTO_INCREMENT,
  `message_type` ENUM('ACTUAL', 'EXERCISE', 'SYSTEM', 'TEST', 'DRAFT') NOT NULL,
  `scope` ENUM('PUBLIC', 'RESTRICTED', 'PRIVATE') NOT NULL,
  `status` ENUM('ACTIVE', 'CANCELED', 'EXPIRED') NOT NULL,
  `urgency` ENUM('IMMEDIATE', 'EXPECTED', 'FUTURE', 'PAST', 'UNKNOWN') NOT NULL,
  `severity` ENUM('EXTREME', 'SEVERE', 'MODERATE', 'MINOR', 'UNKNOWN') NOT NULL,
  `sent_time` VARCHAR(50) NOT NULL,
  `cap_xml` TEXT NOT NULL,
  PRIMARY KEY (`alert_id`))
ENGINE = InnoDB;
