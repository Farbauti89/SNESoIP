<?php

/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

namespace lib;

class myView extends \View{
    
    function render($file,$mime='text/html',array $hive=NULL) {
        global $f3;
        $content = parent::render($file, $mime, $hive);
        
        $f3->set('content', $content);
        
        return parent::render('template.php', $mime, $hive);
    }
    
}
