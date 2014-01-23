<?php

namespace lib;

class Database {
    static private $connections = array();
    
    static public function getConnection($name='default'){
        if(!isset(self::$connections[$name])){
            global $f3;
            $config = new \Doctrine\DBAL\Configuration();
            
            $connectionParams = array(
                'dbname' => $f3->get("database.name"),
                'user' => $f3->get("database.user"),
                'password' => $f3->get("database.password"),
                'host' => $f3->get("database.host"),
                'port' => $f3->get("database.port"),
                'driver' => 'pdo_mysql',
                'charset' => 'UTF8'
            );
            $conn = \Doctrine\DBAL\DriverManager::getConnection($connectionParams, $config);
            
            self::$connections[$name] = $conn;
        }
        
        return self::$connections[$name];
    }
    
}
