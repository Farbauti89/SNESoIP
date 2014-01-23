<?php

use Doctrine\Common\ClassLoader;

function initDoctrine(){
    require 'lib/vendor/doctrine/Doctrine/Common/ClassLoader.php';

    $classLoader = new ClassLoader('Doctrine', 'lib/vendor/doctrine');
    $classLoader->register();
}


initDoctrine();
/* @var $f3 Base */
$f3=require('lib/vendor/f3/base.php');

if(file_exists("config.cfg")){
    $f3->config("config.cfg");
}

$f3->set("UI", "views/");

\lib\Database::getConnection();

$f3->map('/install', 'actions\install\action');

$f3->run();

?>