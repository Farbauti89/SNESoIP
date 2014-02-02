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
        $f3->set('errors', $this->checkDependencies());
        $f3->set('formData', array('dbPort' => '3306'));
        echo \View::instance()->render("install/get.html");
    }
    
    
    
    public function post($f3, $params){
        $template = "install/get.html";
        
        $formData = $f3->get("POST");
        $formErrors = \services\install::validateFormData($formData);
        $this->errors = array();
        
        if(count($formErrors) == 0){
            if(\services\install::writeConfig($formData)){
                //reload config
                $f3->config(self::CONFIG);
                \services\install::createSchema();
            }else{
                $this->errors["Config"] = "Could not write ".self::CONFIG;
            }
        }
        
        $f3->set('formData', $formData);
        $f3->set('formErrors', $formErrors);
        $f3->set('errors', $this->errors);
        
        echo \View::instance()->render($template);
    }
}
