<?php

namespace lib;

class Database {
    static private $connections = array();
    
    /**
     * 
     * @param type $name
     * @return \Doctrine\DBAL\Connection
     */
    static public function getConnection($name='default'){
        if(!isset(self::$connections[$name])){
            $config = new \Doctrine\DBAL\Configuration();
            
            $connectionParams = self::getConnecectionParams();
            $conn = \Doctrine\DBAL\DriverManager::getConnection($connectionParams, $config);
            
            self::$connections[$name] = $conn;
        }
        
        return self::$connections[$name];
    }
    
    static private function getConnecectionParams(){
        
        global $f3;
        
        return array(
                'dbname' => $f3->get("database.name"),
                'user' => $f3->get("database.user"),
                'password' => $f3->get("database.password"),
                'host' => $f3->get("database.host"),
                'port' => $f3->get("database.port"),
                'driver' => 'pdo_mysql',
                'charset' => 'UTF8'
            );
    }
    
    static private $entityManager = null;
    
    /**
     * 
     * @return \Doctrine\ORM\EntityManager
     */
    static public function getEntityManager(){
        
        if(is_null(self::$entityManager)){
            $paths = array("/models");
            $config = \Doctrine\ORM\Tools\Setup::createAnnotationMetadataConfiguration($paths, false);
            
            self::$entityManager = \Doctrine\ORM\EntityManager::create(self::getConnecectionParams(), $config);
        }
        
        return self::$entityManager;
    }
    
}
