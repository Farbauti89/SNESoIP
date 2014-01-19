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
    
    public function get($f3){
        $f3->set('name', 'test');
        $errors = $this->checkDependencies();
        
        $f3->set('errors', $errors);
        echo \View::instance()->render('install/get.html');
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
    
    public function post(){
        echo "verpiss dich !";
    }
}
