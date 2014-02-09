<?php

/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

namespace services;

class install {
    
    /**
     * checks if the System matches the dependencies
     * @return string[]
     */
    static public function checkDependencies(){
        $errors = array();
        
        if (version_compare(phpversion(), "5.3.7", ">=")){
            $hash = '$2y$04$usesomesillystringfore7hnbRJHxXVLeakoG8K30oukPsA.ztMG';
            $test = crypt("password", $hash);
            $pass = $test == $hash;
            if (!$pass){
                    $errors["E_CRYPTERROR"] = "A Crypt error occured.";
            }
        }else{
            $errors["E_UNSUPPORTEDPHPVERSION"] = "Your PHP Version is outdated please upgrade to PHP 5.3.7 or higher.";
        }
        
        return $errors;
    }
    
    /**
     * This Functions creates the Database schema
     */
    static public function createSchema(){
        
        $statements = array();
        
        $statements["userTable"] = <<<EOF
CREATE  TABLE `user` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(255) NOT NULL ,
  `password_hash` VARCHAR(45) NOT NULL ,
  `key` VARCHAR(64) ,
  `is_admin` TINYINT NULL DEFAULT 0 ,
  `online` TINYINT NULL ,
  `create_time` TIMESTAMP NULL DEFAULT NOW() ,
  `auth_time` TIMESTAMP NULL ,
  `current_ip` VARCHAR(128) NULL ,
  `port` INT(10) DEFAULT 0 ,
  `dest_user_id` INT NULL ,
  PRIMARY KEY (`id`) ,
  UNIQUE INDEX `username_UNIQUE` (`username` ASC) ,
  INDEX `online` (`online` ASC));
EOF;
        
        $statements["userFK"] = <<<EOF
ALTER TABLE `user` 
  ADD CONSTRAINT `FK_USER_USER`
  FOREIGN KEY (`dest_user_id` )
  REFERENCES `user` (`id` )
  ON DELETE NO ACTION
  ON UPDATE NO ACTION
, ADD INDEX `FK_USER_USER_idx` (`dest_user_id` ASC) ;            
EOF;
        
        $statements["profile"] = <<<EOF
CREATE  TABLE `profile` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `user_id` INT NOT NULL ,
  `firstname` VARCHAR(255) NULL ,
  `lastname` VARCHAR(255) NULL ,
  `avatar` BLOB NULL ,
  `region` VARCHAR(255) NULL ,
  `email` VARCHAR(255) NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `FK_PROFILE_USER_idx` (`user_id` ASC) ,
  CONSTRAINT `FK_PROFILE_USER`
    FOREIGN KEY (`user_id` )
    REFERENCES `user` (`id` )
    ON DELETE CASCADE
    ON UPDATE NO ACTION);            
EOF;
        
        $connection = \lib\Database::getConnection();
        
        try{
            $connection->connect();
            $connection->beginTransaction();
            
            foreach($statements as $statement){
                $connection->exec($statement);
            }
            
            $connection->commit();
        } catch (Exception $e){
            $connection->rollBack();
            $this->errors['InstallDB'] = $e->getMessage();
        }
    }
    
    /**
     * 
     * @param mixed $data Formdata to validate
     * @return string[]
     */
    static public function validateFormData($data){
        $errors = array();
        
        if($data['adminPassword'] !== $data['adminPasswordVerify']){
            $errors['adminPasswordVerify'] = "Passwords don't match";
        }
        
        return $errors;
    }
    
    static public function writeConfig($formData){
        
        global $f3;
        $fileName = \actions\install\action::CONFIG;
        $templateFileName = \actions\install\action::TEMPLATE_CONFIG;
        
        if(!file_exists($fileName) || is_writable($fileName)){
            //write config
            $configTemplate = $f3->read($templateFileName);
            $newConfig = str_replace("[database.host]", $formData["dbHost"], $configTemplate);
            $newConfig = str_replace("[database.port]", $formData["dbPort"], $newConfig);
            $newConfig = str_replace("[database.name]", $formData["dbName"], $newConfig);
            $newConfig = str_replace("[database.user]", $formData["dbUserName"], $newConfig);
            $newConfig = str_replace("[database.password]", $formData["dbPassword"], $newConfig);

            $f3->write($fileName, $newConfig);
            
            return true;
        }
        
        return false;
        
    }
    
    static public function createAdmin($formData){
        $entityManager = \lib\Database::getEntityManager();
        
        $user = new \models\user();
        
        $user->setUsername($formData['adminName']);
        $user->setPasswordHash(md5($formData['adminPassword']));
        $user->setIsAdmin(true);
        
        $entityManager->persist($user);
        $entityManager->flush();
    }
    
}
