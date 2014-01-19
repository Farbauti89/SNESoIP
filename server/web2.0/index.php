<?php

/* @var $f3 Base */
$f3=require('lib/vendor/f3/base.php');
$f3->config("config.cfg");
if(file_exists("user_config.cfg")){
    $f3->config("user_config.cfg");
}

\lib\Database::getConnection();

$f3->map('/install', 'actions\install\action');

$f3->run();

?>