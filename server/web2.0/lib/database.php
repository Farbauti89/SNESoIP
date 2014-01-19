<?php

namespace lib;

class Database {
    static private $connections = array();
    
    static public function getConnection($name='work'){
        if(!isset(self::$connections[$name])){
            $prefix = "database.".$name.".";
            $f3 = \Base::instance();
            
            $dns = sprintf('mysql:host=%s;port=%s;dbname=%s', $f3->get($prefix."host"), $f3->get($prefix."port"), $f3->get($prefix."name"));
            $db = new \DB\SQL($dns, $f3->get($prefix."user"), $f3->get($prefix."password"));
            
            self::$connections[$name] = $db;
        }
        
        return self::$connections[$name];
    }
    
}
