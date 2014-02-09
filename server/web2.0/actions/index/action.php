<?php
/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

namespace actions\index;


class action {
    
    public function get($f3){
        echo \lib\myView::instance()->render('index/login.php');
    }
    
    public function post($f3){
        
    }
}
