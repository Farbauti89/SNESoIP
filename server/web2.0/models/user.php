<?php

/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

/**
 * @Entity @Table(name="user")
 **/
class User {
    
    /**
     * @Id @Column(type="integer") @GeneratedValue
     * @var int 
     */
    private $id;
    
    /**
     * @Column(type="string", length=32)
     * @var string
     */
    private $username;
    
    /**
     * @Column(type="string", length=255, unique="true")
     * @var string
     */
    private $password;
    
    /**
     * @Column(type="datetime", name="created_time", nullable=true)
     * @var DateTime 
     */
    private $createTime;
    
    /**
     * @Column(type=boolean, name="admin", nullable=true)
     * @var boolean 
     */
    private $isAdmin;
    
    /**
     * @Column(type="string", length=128)
     * @var string
     */
    private $currentIp;
    
    /**
     * @Column(type="integer", length=10, options={unsigned=true, default="0"})
     * @var integer 
     */
    private $port;
    
    /**
     * @Column(type="boolean", options={default="0"})
     * @var boolean 
     */
    private $online;
    
    /**
     * @Column(type="datetime", name="auth_time")
     * @var DateTime 
     */
    private $authTime;
            
    /**
     * @OneToOne(targetEntity="User")
     * @JoinColumn(name="dest_user_id", referencedColumnName="id") 
     */
    private $destUser;
    
    /**
     * @Column(type="string", length=64)
     * @var string
     */
    private $key;
            
}
