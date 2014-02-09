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
 * @Entity @Table(name="profile")
 **/
class profile {
    
    /**
     * @Id @Column(type="integer") @GeneratedValue
     * @var int 
     */
    private $id;
    
    /**
     * @Column(type="string", length=255)
     * @var string
     */
    private $firstname;
    
    /**
     * @Column(type="string", length=255)
     * @var string
     */
    private $lastname;
    
    /**
     * @Column(type="blob")
     * @var blob
     */
    private $avatar;
    
    /**
     * @Column(type="string", length=255)
     * @var string
     */
    private $region;
    
    /**
     * @Column(type="string", length=255)
     * @var string
     */
    private $email;
    
    /**
     * @OneToOne(targetEntity="user", inversedBy="profile", cascade="persist")
     * @JoinColumn(name="user_id", referencedColumnName="id")
     */
    private $user;
    
    public function getId() {
        return $this->id;
    }

    public function getFirstname() {
        return $this->firstname;
    }

    public function getLastname() {
        return $this->lastname;
    }

    public function getAvatar() {
        return $this->avatar;
    }

    public function getRegion() {
        return $this->region;
    }

    public function getEmail() {
        return $this->email;
    }

    public function setId($id) {
        $this->id = $id;
        return $this;
    }

    public function setFirstname($firstname) {
        $this->firstname = $firstname;
        return $this;
    }

    public function setLastname($lastname) {
        $this->lastname = $lastname;
        return $this;
    }

    public function setAvatar(blob $avatar) {
        $this->avatar = $avatar;
        return $this;
    }

    public function setRegion($region) {
        $this->region = $region;
        return $this;
    }

    public function setEmail($email) {
        $this->email = $email;
        return $this;
    }
    
    public function getUser(){
        return $this->user;
    }
    
    public function setUser(User $user){
        $this->user = $user;
        return $this;
    }


}
