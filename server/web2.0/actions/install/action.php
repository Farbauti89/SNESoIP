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
        $errors = $this->checkDependencies();
        
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
                
                
            }else{
                $errors["Config"] = "Could not write ".self::CONFIG;
            }
        }
        
        $f3->set('formData', $formData);
        $f3->set('formErrors', $formErrors);
        $f3->set('errors', $errors);
        
        echo \View::instance()->render($template);
    }
    
    private function validateFormData($data){
        $errors = array();
        
        if($data['adminPassword'] !== $data['adminPasswordVerify']){
            $errors['adminPasswordVerify'] = "Passwords don't match";
        }
        
        return $errors;
    }
}
