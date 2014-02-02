<?php

/*
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. 
 *
 * Author: Jan Schmitz
 */

namespace models;

/**
 * @Entity @Table(name="user")
 **/
class user {
    
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
     * @OneToOne(targetEntity="Profile")
     * @JoinColumn(name="id", referencedColumnName="user_id") 
     */
    private $profile;
    
    /**
     * @Column(type="string", length=64)
     * @var string
     */
    private $key;
    
    public function getId() {
        return $this->id;
    }

    public function getUsername() {
        return $this->username;
    }

    public function getPassword() {
        return $this->password;
    }

    public function getCreateTime() {
        return $this->createTime;
    }

    public function getIsAdmin() {
        return $this->isAdmin;
    }

    public function getCurrentIp() {
        return $this->currentIp;
    }

    public function getPort() {
        return $this->port;
    }

    public function getOnline() {
        return $this->online;
    }

    public function getAuthTime() {
        return $this->authTime;
    }

    public function getDestUser() {
        return $this->destUser;
    }

    public function getKey() {
        return $this->key;
    }

    public function setId($id) {
        $this->id = $id;
        return $this;
    }

    public function setUsername($username) {
        $this->username = $username;
        return $this;
    }

    public function setPassword($password) {
        $this->password = $password;
        return $this;
    }

    public function setCreateTime(DateTime $createTime) {
        $this->createTime = $createTime;
        return $this;
    }

    public function setIsAdmin($isAdmin) {
        $this->isAdmin = $isAdmin;
        return $this;
    }

    public function setCurrentIp($currentIp) {
        $this->currentIp = $currentIp;
        return $this;
    }

    public function setPort($port) {
        $this->port = $port;
        return $this;
    }

    public function setOnline($online) {
        $this->online = $online;
        return $this;
    }

    public function setAuthTime(DateTime $authTime) {
        $this->authTime = $authTime;
        return $this;
    }

    public function setDestUser($destUser) {
        $this->destUser = $destUser;
        return $this;
    }

    public function setKey($key) {
        $this->key = $key;
        return $this;
    }

    public function getProfile() {
        return $this->profile;
    }

    public function setProfile($profile) {
        $this->profile = $profile;
        return $this;
    }


            
}
