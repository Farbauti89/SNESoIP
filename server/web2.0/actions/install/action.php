<?php

/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

namespace actions\install;

class action {
    
    private $errors = array();
    
    CONST TEMPLATE_CONFIG = "config.default.cfg";
    CONST CONFIG = "config.cfg";
    
    public function get($f3){
        $f3->set('name', 'test');
        
        $f3->set('errors', $this->checkDependencies());
        
        $f3->set('formData', array('dbPort' => '3306'));
        echo \View::instance()->render("install/get.html");
    }
    
    private function checkDependencies(){
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
    
    public function post($f3, $params){
        $template = "install/get.html";
        
        $formData = $f3->get("POST");
        $formErrors = $this->validateFormData($formData);
        $this->checkDependencies();
        
        if(count($formErrors) == 0){
            if(!file_exists(self::CONFIG) || is_writable(self::CONFIG)){
                //write config
                $configTemplate = $f3->read(self::TEMPLATE_CONFIG);
                $newConfig = str_replace("[database.host]", $formData["dbHost"], $configTemplate);
                $newConfig = str_replace("[database.port]", $formData["dbPort"], $newConfig);
                $newConfig = str_replace("[database.name]", $formData["dbName"], $newConfig);
                $newConfig = str_replace("[database.user]", $formData["dbUserName"], $newConfig);
                $newConfig = str_replace("[database.password]", $formData["dbPassword"], $newConfig);

                $f3->write(self::CONFIG, $newConfig);
                
                //reload config
                $f3->config(self::CONFIG);
                $this->createSchema();
                
                
            }else{
                $this->errors["Config"] = "Could not write ".self::CONFIG;
            }
        }
        
        $f3->set('formData', $formData);
        $f3->set('formErrors', $formErrors);
        $f3->set('errors', $this->errors);
        
        echo \View::instance()->render($template);
    }
    
    private function validateFormData($data){
        if($data['adminPassword'] !== $data['adminPasswordVerify']){
            $this->errors['adminPasswordVerify'] = "Passwords don't match";
        }
    }
    
    private function createSchema(){
        
        $statements = array();
        
        $statements["userTable"] = <<<EOF
CREATE  TABLE `user` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `username` VARCHAR(255) NOT NULL ,
  `password_hash` VARCHAR(45) NOT NULL ,
  `key` VARCHAR(64) NOT NULL ,
  `isAdmin` TINYINT NULL DEFAULT 0 ,
  `online` TINYINT NULL ,
  `create_time` TIMESTAMP NULL DEFAULT NOW() ,
  `auth_time` TIMESTAMP NULL ,
  `current_ip` VARCHAR(128) NULL ,
  `port` INT(10) NOT NULL DEFAULT 0 ,
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
}
