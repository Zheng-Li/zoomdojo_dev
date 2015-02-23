<?php

class zportfolio {

  private $uid = null;
  private $a = null;
  private $fields = array(
    'general_data'=>array(
      'id'=>null,
      'name'=>array(
        'title'=>'Your name',
        'maxlength'=>255,
        'required'=>TRUE
      ),
      'address'=>array(
        'title'=>'Address',
        'required'=>TRUE
      ),
      'cellphone'=>array(
        'title'=>'Cell Phone',
        'maxlength'=>255,
        'required'=>TRUE
      ),
      'email'=>array(
        'title'=>'Email',
        'maxlength'=>255,
        'required'=>TRUE,
        'filter'=>'email'
      ),
      'other'=>array(
        'title'=>'Others',
      )
    ),
    'education'=>array(
      'institution'=>array(
        'title'=>'Name of Institution',
        'maxlength'=>255,
        'required'=>TRUE,
      ),
      'city'=>array(
        'title'=>'City',
        'maxlength'=>255
      ),
      'state'=>array(
        'title'=>'State',
        'maxlength'=>255
      ),
      'country'=>array(
        'title'=>'Country',
        'maxlength'=>255
      ),
      'course'=>array(
        'title'=>'Degree / Name of Course',
        'maxlength'=>255
      ),
      'date_type'=>array(
        'filter'=>'integer'
      ),
      'start_year'=>array(
        'title'=>'Attended from Year',
        'maxlength'=>4,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'start_mounth'=>array(
        'title'=>'Attended from Mounth',
        'maxlength'=>2,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'currently_studying'=>array(
        'title'=>'Currently Studying',
        'filter'=>'integer'
      ),
      'end_year'=>array(
        'title'=>'End Year',
        'maxlength'=>4,
       'filter'=>'end_year'
      ),
      'end_mounth'=>array(
        'title'=>'End Mounth',
        'maxlength'=>2,
        'filter'=>'integer'
      ),
      'major'=>array(
        'title'=>'Major GPA',
        'maxlength'=>500,
      ),
      'minor'=>array(
        'title'=>'Minor (s)',
        'maxlength'=>500,
      ),
      'cumulativegpa'=>array(
        'title'=>'Cumulative GPA',
        'maxlength'=>500,
      ),
      'honors'=>array(
        'title'=>'Honors / Awards',
      ),
      'coursework'=>array(
        'coursework'=>array(
          'title'=>'Relevant Coursework'
        )
      )
    ),
    'experience'=>array(
      'organization'=>array(
        'title'=>'Name of Organization',
        'maxlength'=>100,
        'required'=>TRUE
      ),
      'jobtitle'=>array(
        'title'=>'Job Title',
        'maxlength'=>500,
        'required'=>TRUE
      ),
      'city'=>array(
        'title'=>'City',
        'maxlength'=>255
      ),
      'state'=>array(
        'title'=>'State',
        'maxlength'=>255
      ),
      'country'=>array(
        'title'=>'Country',
        'maxlength'=>255
      ),
      'date_type'=>array(
          'filter'=>'integer'
      ),
      'start_year'=>array(
        'title'=>'Time Period Worked From Year',
        'maxlength'=>4,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'start_mounth'=>array(
        'title'=>'Time Period Worked From Mounth',
        'maxlength'=>2,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'end_year'=>array(
        'title'=>'End Year',
        'maxlength'=>4,
       'filter'=>'end_year'
      ),
      'end_mounth'=>array(
        'title'=>'End Mounth',
        'maxlength'=>2,
        'filter'=>'integer'
      ),
      'responsibility'=>array(
        'responsibility'=>array(
          'title'=>'Job Responsibility',
          'maxlength'=>500,
          'required'=>TRUE
        ),
        'achievement'=>array(
          'title'=>'Achievement',
          'maxlength'=>500
        )
      )
    ),
    'leadership'=>array(
      'organization'=>array(
        'title'=>'Name of Organization',
        'maxlength'=>100,
        'required'=>TRUE
      ),
      'designationtitle'=>array(
        'title'=>'Title',
        'maxlength'=>45
      ),
      'city'=>array(
        'title'=>'City',
        'maxlength'=>255
      ),
      'state'=>array(
        'title'=>'State',
        'maxlength'=>255
      ),
      'country'=>array(
        'title'=>'Country',
        'maxlength'=>255
      ),
      'date_type'=>array(
            'filter'=>'integer'
      ),
      'start_year'=>array(
        'title'=>'Time Period Worked From Year',
        'maxlength'=>4,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'start_mounth'=>array(
        'title'=>'Time Period Worked From Mounth',
        'maxlength'=>2,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'end_year'=>array(
        'title'=>'End Year',
        'maxlength'=>4,
       'filter'=>'end_year'
      ),
      'end_mounth'=>array(
        'title'=>'End Mounth',
        'maxlength'=>2,
        'filter'=>'integer'
      ),
      'details'=>array(
        'title'=>'Details',
      ),
      'responsibility'=>array(
        'more_details'=>array(
          'title'=>'Title',
          'maxlength'=>500,
          'required'=>TRUE
        ),
      )
    ),
    'volunteer'=>array(
      'organization'=>array(
        'title'=>'Name of Organization',
        'maxlength'=>100
      ),
      'designationtitle'=>array(
        'title'=>'Title',
        'maxlength'=>45
      ),
      'city'=>array(
        'title'=>'City',
        'maxlength'=>255
      ),
      'state'=>array(
        'title'=>'State',
        'maxlength'=>255
      ),
      'country'=>array(
        'title'=>'Country',
        'maxlength'=>255
      ),
      'start_year'=>array(
        'title'=>'Time Period Worked From Year',
        'maxlength'=>4,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
        'date_type'=>array(
            'filter'=>'integer'
        ),
      'start_mounth'=>array(
        'title'=>'Time Period Worked From Mounth',
        'maxlength'=>2,
        'required'=>TRUE,
        'filter'=>'integer'
      ),
      'end_year'=>array(
        'title'=>'End Year',
        'maxlength'=>4,
       'filter'=>'end_year'
      ),
      'end_mounth'=>array(
        'title'=>'End Mounth',
        'maxlength'=>2,
        'filter'=>'integer'
      ),
      'description'=>array(
        'title'=>'Description'
      ),
      'responsibility'=>array(
        'more_details'=>array(
           'title'=>'Title',
           'maxlength'=>500,
           'required'=>TRUE
        ),
      )
    ),
    'skills'=>array(
      'type'=>array(
        'title'=>'Skill type',
        'required'=>TRUE,
      ),
      'val1'=>array(
        'title'=>'Skill value',
        'maxlength'=>255,
        'required'=>TRUE,
      ),
      'val2'=>array(
        'title'=>'Skill value',
        'maxlength'=>255
      ),
      'val3'=>array(
        'title'=>'Skill value',
        'maxlength'=>255
      ),
      'val4'=>array(
        'title'=>'Skill value',
        'maxlength'=>255
      ),
      'val5'=>array(
        'title'=>'Skill value',
        'maxlength'=>255
      )
    ),
    'custom'=>array(
      'title'=>Array(
        'title'=>'Title',
        'maxlength'=>100,
        'required'=>TRUE
      ),
      'items'=>array(
        'start_year'=>array(
          'title'=>'From',
          'maxlength'=>4,
          'required'=>TRUE,
          'filter'=>'integer'
        ),
        'start_mounth'=>array(
          'title'=>'To',
          'maxlength'=>2,
          'required'=>TRUE,
          'filter'=>'integer'
        ),
        'end_year'=>array(
          'title'=>'End Year',
          'maxlength'=>4,
         'filter'=>'end_year'
        ),
        'end_mounth'=>array(
          'title'=>'End Mounth',
          'maxlength'=>2,
          'filter'=>'integer'
        ),
        'details'=>array(
          'title'=>'Details',
        )
      )
    )
  );
  
  // error log
  private $status = array();
  private $error = array();
  
  public function __construct($uid) {
    $this->uid = $uid;
    return $this->load();
  }
  
 /**
 * Load a portfolio for a given user from the database
 *
 * @return void
 */
  public function load(){
    $result = db_query('select * FROM user_portfolio where uid=:uid '
        . 'ORDER BY education_prior DESC, education_id DESC, '
        . 'experience_prior DESC, experience_id DESC, '
        . 'leadership_prior DESC, leadership_id DESC, '
        . 'volunteer_prior DESC, volunteer_id DESC, '
        . 'custom_id ASC, custom_item_prior DESC, custom_item_id DESC', array(':uid' => $this->uid));
    if($result->rowCount()){

      foreach ($result as $row) {

        // general
        $this->fields['general_data']['data']['id'] = (int)$row->id;
        $this->fields['general_data']['data']['name'] = $row->name;
        $this->fields['general_data']['data']['address'] = $row->address;
        $this->fields['general_data']['data']['cellphone'] = $row->cellphone;
        $this->fields['general_data']['data']['email'] = $row->email;
        $this->fields['general_data']['data']['other'] = $row->other;
        
        // education
        if(!is_null($row->education_id)){
          $this->fields['education']['data'][$row->education_id]['institution']
              = $row->education_institution;
          $this->fields['education']['data'][$row->education_id]['city']
              = $row->education_city;
          $this->fields['education']['data'][$row->education_id]['state']
              = $row->education_state;
          $this->fields['education']['data'][$row->education_id]['country']
              = $row->education_country;
          $this->fields['education']['data'][$row->education_id]['course']
              = $row->education_course;
          $this->fields['education']['data'][$row->education_id]['date_type']
              = (int)$row->education_date_type;
          $this->fields['education']['data'][$row->education_id]['start_mounth']
              = (int)$row->education_start_mounth;
          $this->fields['education']['data'][$row->education_id]['start_year']
              = (int)$row->education_start_year;
          $this->fields['education']['data'][$row->education_id]['currently_studying']
              = (int)$row->education_currently_studying;
          $this->fields['education']['data'][$row->education_id]['end_mounth']
              = (int)$row->education_end_mounth;
          $this->fields['education']['data'][$row->education_id]['end_year']
              = (int)$row->education_end_year;
          $this->fields['education']['data'][$row->education_id]['major']
              = $row->education_major;
          $this->fields['education']['data'][$row->education_id]['minor']
              = $row->education_minor;
          $this->fields['education']['data'][$row->education_id]['cumulativegpa']
              = $row->education_cumulativegpa;
          $this->fields['education']['data'][$row->education_id]['honors']
              = $row->education_honors;
          
          if(!is_null($row->education_coursework_id)){
            $this->fields['education']['data'][$row->education_id]['coursework'][$row->education_coursework_id]
                = array(
                  'coursework'=>$row->education_coursework_coursework
                );
          }
        }
        
        // experience
        if(!is_null($row->experience_id)){
          $this->fields['experience']['data'][$row->experience_id]['organization']
              = $row->experience_organization;
          $this->fields['experience']['data'][$row->experience_id]['jobtitle']
              = $row->experience_jobtitle;
          $this->fields['experience']['data'][$row->experience_id]['city']
              = $row->experience_city;
          $this->fields['experience']['data'][$row->experience_id]['state']
              = $row->experience_state;
          $this->fields['experience']['data'][$row->experience_id]['country']
              = $row->experience_country;
          $this->fields['experience']['data'][$row->experience_id]['date_type']
              = $row->experience_date_type;
          $this->fields['experience']['data'][$row->experience_id]['start_mounth']
              = (int)$row->experience_start_mounth;
          $this->fields['experience']['data'][$row->experience_id]['start_year']
              = (int)$row->experience_start_year;
          $this->fields['experience']['data'][$row->experience_id]['end_mounth']
              = (int)$row->experience_end_mounth;
          $this->fields['experience']['data'][$row->experience_id]['end_year']
              = (int)$row->experience_end_year;
          
          if(!is_null($row->experience_responsibility_id)){
            $this->fields['experience']['data'][$row->experience_id]['responsibility'][$row->experience_responsibility_id]
                = array(
                  'responsibility'=>$row->experience_responsibility_responsibility,
                  'achievement'=>$row->experience_responsibility_achievement
                );
          }
        }
        
        // leadership
        if(!is_null($row->leadership_id)){
          $this->fields['leadership']['data'][$row->leadership_id]['organization']
              = $row->leadership_organization;
          $this->fields['leadership']['data'][$row->leadership_id]['designationtitle']
              = $row->leadership_designationtitle;
          $this->fields['leadership']['data'][$row->leadership_id]['city']
              = $row->leadership_city;
          $this->fields['leadership']['data'][$row->leadership_id]['state']
              = $row->leadership_state;
          $this->fields['leadership']['data'][$row->leadership_id]['country']
              = $row->leadership_country;
          $this->fields['leadership']['data'][$row->leadership_id]['date_type']
              = (int)$row->leadership_date_type;
          $this->fields['leadership']['data'][$row->leadership_id]['start_mounth']
              = (int)$row->leadership_start_mounth;
          $this->fields['leadership']['data'][$row->leadership_id]['start_year']
              = (int)$row->leadership_start_year;
          $this->fields['leadership']['data'][$row->leadership_id]['end_mounth']
              = (int)$row->leadership_end_mounth;
          $this->fields['leadership']['data'][$row->leadership_id]['end_year']
              = (int)$row->leadership_end_year;
          $this->fields['leadership']['data'][$row->leadership_id]['details']
              = $row->leadership_details;
          
          if(!is_null($row->leadership_responsibility_id)){
            $this->fields['leadership']['data'][$row->leadership_id]['responsibility'][$row->leadership_responsibility_id]
                = array(
                  'more_details'=>$row->leadership_responsibility_more_details,
                );
          }
        }
        
        // skills
        if(!is_null($row->skill_id)){
          $this->fields['skills']['data'][$row->skill_type][$row->skill_id] = array(
            'val1'=>$row->skill_val1,
            'val2'=>$row->skill_val2,
            'val3'=>$row->skill_val3,
            'val4'=>$row->skill_val4,
            'val5'=>$row->skill_val5
          );
        }
        
        // custom sections
        if(!is_null($row->custom_id)){
          $this->fields['custom']['data'][$row->custom_id]['title']
              = $row->custom_title;
          
          if(!is_null($row->custom_item_id)){
            $this->fields['custom']['data'][$row->custom_id]['items'][$row->custom_item_id]
                = array(
                  'title'=>$row->custom_item_title,
                  'date_type'=>$row->custom_item_date_type,
                  'start_mounth'=> (int)$row->custom_item_start_mounth,
                  'start_year'=>(int)$row->custom_item_start_year,
                  'end_mounth'=>(int)$row->custom_item_end_mounth,
                  'end_year'=>(int)$row->custom_item_end_year,
                  'description'=>$row->custom_item_description
                );
          }
        }

        // volunteer
        if(!is_null($row->volunteer_id)){

            $this->fields['volunteer']['data'][$row->volunteer_id]['organization']
                = $row->volunteer_organization;
            $this->fields['volunteer']['data'][$row->volunteer_id]['designationtitle']
                = $row->volunteer_designationtitle;
            $this->fields['volunteer']['data'][$row->volunteer_id]['city']
                = $row->volunteer_city;
            $this->fields['volunteer']['data'][$row->volunteer_id]['state']
                = $row->volunteer_state;
            $this->fields['volunteer']['data'][$row->volunteer_id]['country']
                = $row->volunteer_country;
            $this->fields['volunteer']['data'][$row->volunteer_id]['date_type']
                = (int)$row->volunteer_date_type;
            $this->fields['volunteer']['data'][$row->volunteer_id]['start_mounth']
                = (int)$row->volunteer_start_mounth;
            $this->fields['volunteer']['data'][$row->volunteer_id]['start_year']
                = (int)$row->volunteer_start_year;
            $this->fields['volunteer']['data'][$row->volunteer_id]['end_mounth']
                = (int)$row->volunteer_end_mounth;
            $this->fields['volunteer']['data'][$row->volunteer_id]['end_year']
                = (int)$row->volunteer_end_year;
            $this->fields['volunteer']['data'][$row->volunteer_id]['description']
                = $row->volunteer_description;

            if(!is_null($row->volunteer_responsibility_id)){
              $this->fields['volunteer']['data'][$row->volunteer_id]['responsibility'][$row->volunteer_responsibility_id]
                = array(
                 'more_details'=>$row->volunteer_responsibility_more_details,
                );
          }
        }
      }
      
    }
  }
  
 /**
 * Checks whether a portfolio for a given user exists in the database
 *
 * @return boolean
 */
  public function exist(){
    return !is_null($this->id);
  }
  
  /**
   * Saving portfolio for a given user to the database
   *
   * $data array
   * 
   * @return void
   */
  public function save($data){

    if(!is_array($data)){
      $error = t('Datatype mismatch.');
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    } 
    $type_data = array();
    foreach($this->fields as $type=>$fields){
      foreach($this->fields[$type] as $field=>$rule){
        if($type == 'general_data'){
          if($this->check($rule,'',$field,$data,$type)){
            if(!isset($data[$field])){
              $type_data[$type][$field] = null;
            }else{
              $type_data[$type][$field] = is_string($data[$field])
                                        ?strip_tags($data[$field])
                                        :$data[$field];
            }
          }
        }else{
          if($type == 'skills' && $field == 'type'){
            $skills = array();
            if(array_key_exists('skills', $data) && sizeof($data['skills'])){
              foreach($data['skills'] as $stype=>$skill){
                foreach($skill as $sid=>$skill_el){
                  if($sid === 'new'){
                    foreach($skill[$sid] as $snid=>$snkill_el){
                      $skills[$sid][] = array(
                        'type'=>$stype,
                        'val1'=>isset($snkill_el['val1'])
                                ?strip_tags($snkill_el['val1'])
                                :null,
                        'val2'=>isset($snkill_el['val2'])
                                ?strip_tags($snkill_el['val2'])
                                :null,
                        'val3'=>isset($snkill_el['val3'])
                                ?strip_tags($snkill_el['val3'])
                                :null,
                        'val4'=>isset($snkill_el['val4'])
                                ?strip_tags($snkill_el['val4'])
                                :null,
                        'val5'=>isset($snkill_el['val5'])
                                ?strip_tags($snkill_el['val5'])
                                :null,
                      );
                    }
                  }elseif($stype === 'delete'){
                     $skills[$stype][] = $skill_el;
                  }else{
                    $skills[$sid] = array(
                      'type'=>$stype,
                      'val1'=>isset($skill_el['val1'])
                              ?strip_tags($skill_el['val1'])
                              :null,
                      'val2'=>isset($skill_el['val2'])
                              ?strip_tags($skill_el['val2'])
                              :null,
                      'val3'=>isset($skill_el['val3'])
                              ?strip_tags($skill_el['val3'])
                              :null,
                      'val4'=>isset($skill_el['val4'])
                              ?strip_tags($skill_el['val4'])
                              :null,
                      'val5'=>isset($skill_el['val5'])
                              ?strip_tags($skill_el['val5'])
                              :null,
                    );
                  }
                }
              }
            }
            $data['skills']=$skills;
          }
          if(isset($data[$type]['new'])){
            foreach($data[$type]['new'] as $i=>$sdata){
              if($this->check($rule,'',$field,$sdata,$type,$i,true)){
                if(!isset($sdata[$field])){
                  $type_data[$type]['n'.$i][$field] = null;
                }else{
                  $type_data[$type]['n'.$i][$field] =  is_string($sdata[$field])
                                      ?strip_tags($sdata[$field])
                                      :$sdata[$field];
                }
              }
              if($field == 'responsibility' && isset($sdata['responsibility']) && sizeof($sdata['responsibility'])){
                $this->check_responsibility($rule,$sdata['responsibility'],$type,$i,true);
              }
              if($field == 'coursework' && isset($sdata['coursework']) && sizeof($sdata['coursework'])){
                $this->check_responsibility($rule,$sdata['coursework'],$type,$i,true,'coursework');
              }
              if($field == 'items' && isset($sdata['items']) && sizeof($sdata['items'])){
                $this->check_responsibility($rule,$sdata['items'],$type,$i,true,'items');
              }
            }
          }
          if(isset($data[$type]['delete'])){
            if(in_array($type,array_keys($this->fields))){
              foreach($data[$type]['delete'] as $did){
                db_delete("users_portfolio_{$type}")
                  ->condition('id', $did)
                  ->execute();
              }
            }
            if(isset($this->fields[$type]['data'])){
              $this->fields[$type]['data'] = array_diff_key($this->fields[$type]['data'],
                  array_flip($data[$type]['delete']));
            }
            unset($data[$type]['delete']);
          }
          if(isset($data[$type]) && sizeof($data[$type])){
            foreach($data[$type] as $id=>$sdata){
              if($id == 'new' || $id == 'delete' 
                  || (isset($data[$type]['delete']) && in_array($id, $data[$type]['delete']))){
                continue;
              }
              if($this->check($rule,'',$field,$sdata,$type,$id)){
                if(isset($sdata[$field]) && is_array($sdata[$field])){
                  array_walk($sdata[$field], create_function('&$val', 'foreach($val as &$text){$text = is_string($text)?strip_tags($text):$text;}')); 
                }
                $type_data[$type][$id][$field] = isset($sdata[$field])
                                      ?(is_string($sdata[$field])?strip_tags($sdata[$field]):$sdata[$field])
                                      :null;
              }
              if(
                  ($field == 'responsibility' && isset($sdata['responsibility']) && sizeof($sdata['responsibility']))
                  || ($field == 'coursework' && isset($sdata['coursework']) && sizeof($sdata['coursework']))
                  || ($field == 'items' && isset($sdata['items']) && sizeof($sdata['items']))
              ){
                if(isset($sdata[$field]['delete'])){
                  foreach($sdata[$field]['delete'] as $did){
                    db_delete("users_portfolio_{$type}_{$field}")
                      ->condition('id', $did)
                      ->execute();
                    unset($type_data[$type][$id][$field][$did],
                        $sdata[$field][$did],
                        $data[$type][$id][$field][$did],
                        $this->fields[$type]['data'][$id][$field][$did]);
                  }
                  unset($sdata[$field]['delete'],
                      $data[$type][$id][$field]['delete'],
                      $type_data[$type][$id][$field]['delete'],
                          $this->fields[$type]['data'][$id][$field]['delete']);
                }
                
                $this->check_responsibility($rule,$sdata[$field],$type,$id, false, $field);
              }
            }
          }
        }
      }
    }
    foreach ($type_data as $type=>$data) {
      foreach ($data as $key=>$sdata) {
        if(preg_match("/^n\d+/", $key, $matches)){
          unset($type_data[$type][$key]);
          $type_data[$type][$key] = $sdata;
        }
      }
    }
    
    if($this->getStatus()){
      foreach($this->fields as $type=>$fields){
        if(isset($type_data[$type]) && sizeof($type_data[$type]) && $this->getStatus()){
          $type_data[$type]['data'] = 
              call_user_func( array(
                    $this,
                    "save_".($type == 'general_data'?'general_data':'data')
                  ),
                $type,
                $type_data[$type]
              );
        }
      }
    }
    
    if($this->getStatus()){
        foreach($this->fields as $type=>$fields){
          if(isset($type_data[$type])){
            $this->fields[$type]['data'] = 
                array_replace_recursive(
                    $type=='general_data'?$this->fields[$type]['data']:$this->$type,
                    $type_data[$type]['data']
                );
          }
        }
    }else{
      foreach($this->fields as $type=>$fields){
        if($type == 'general_data'){
          $this->fields[$type]['data'] = array_replace_recursive($this->fields[$type]['data'],
              array_intersect_key($data,$this->fields[$type]));
        }elseif(array_key_exists($type,$data)){
          if(array_key_exists('data',$this->fields[$type])){
            $this->fields[$type]['data'] = array_replace_recursive($this->fields[$type]['data'],$data[$type]);
          }else{
            $this->fields[$type]['data'] = $data[$type];  
          }
        }
      }
    }
    if(isset($this->fields['skills']['data']) && sizeof($this->fields['skills']['data'])){
      $skills = array();
      foreach($this->fields['skills']['data'] as $sid=>$skill){
          if($sid === 'new'){
            foreach($skill as $nid=>$nskill){
              $skills[$nskill['type']]['new'][$nid] = array(
                'val1'=>isset($nskill['val1'])
                        ?strip_tags($nskill['val1'])
                        :null,
                'val2'=>isset($nskill['val2'])
                        ?strip_tags($nskill['val2'])
                        :null,
                'val3'=>isset($nskill['val3'])
                        ?strip_tags($nskill['val3'])
                        :null,
                'val4'=>isset($nskill['val4'])
                        ?strip_tags($nskill['val4'])
                        :null,
                'val5'=>isset($nskill['val5'])
                        ?strip_tags($nskill['val5'])
                        :null,
              );
            }
          }elseif(isset($skill['type'])){
            $skills[$skill['type']][$sid] = array(
              'val1'=>isset($skill['val1'])
                      ?strip_tags($skill['val1'])
                      :null,
              'val2'=>isset($skill['val2'])
                      ?strip_tags($skill['val2'])
                      :null,
              'val3'=>isset($skill['val3'])
                      ?strip_tags($skill['val3'])
                      :null,
              'val4'=>isset($skill['val4'])
                      ?strip_tags($skill['val4'])
                      :null,
              'val5'=>isset($skill['val5'])
                      ?strip_tags($skill['val5'])
                      :null,
            );
            ksort($skills[$skill['type']]);
          }
      }
      ksort($skills);
      $this->fields['skills']['data']=$skills;
    }
    return $this->getStatus();
  }
  
  /**
   * Inserting/Updating `users_portfolio` table
   *
   * $data array
   * 
   * @return void
   */
  private function save_general_data($type,$general_data){
    try {
      $status = db_merge('users_portfolio')
        ->key(array('id' => isset($this->fields['general_data']['data'])
                            ?$this->fields['general_data']['data']['id']
                            :null))
        ->fields(array_merge($general_data,array('users_uid'=>$this->uid)))
        ->execute();
      if( $status == MergeQuery::STATUS_INSERT ) {
        $general_data['id'] = 
          db_query("SELECT LAST_INSERT_ID()")->fetchField();
        $this->fields['general_data']['data']['id'] = $general_data['id'];
      }else{
        $general_data['id'] = $this->fields['general_data']['data']['id'];
      }
    }
    catch (Exception $e) {
      $error = $e->errorInfo[2];
      $this->status[] =$error;
      drupal_set_message($error,'error');
    }
    return $general_data;
  }
  
  /**
   * Inserting/Updating `users_portfolio_experience` and 
   * `users_portfolio_experience_responsibility` tables
   *
   * $data array
   * 
   * @return void
   */
  private function save_data($type,$data){

    $types_with_prior = array(
      'education',
      'experience',
      'leadership',
      'volunteer'
    );

    $return = $this->$type;
    $prior = sizeof($data);
    foreach($data as $id=>$element){
      if(isset($element['start_year'])){
        $element['year_start'] = $element['start_year'];
        $element['mounth_start'] = $element['start_mounth'];
      }
      if(isset($element['end_year']) && $element['end_year']>0
          && isset($element['end_mounth']) 
          && $element['end_mounth']>=0){
        $element['year_end'] = $element['end_year'];
        $element['mounth_end'] = $element['end_mounth'];
      }elseif(isset($element['start']) && (!isset($element['end']) || $element['end']== 0)){
        $element['end'] = null;
      }
      if(isset($element['start_year'])){
        $date_tmp = array(
            'start_year'=>$element['start_year'],
            'start_mounth'=>$element['start_mounth'],
            'end_year'=>$element['end_year'],
            'end_mounth'=> $element['end_mounth']
        );
      }
      unset($element['start_year'],$element['start_mounth'],
            $element['end_year'],$element['end_mounth']);
      $merge_fields = array('users_portfolio_id'=>$this->fields['general_data']['data']['id']);
      if(in_array($type,$types_with_prior)){
        $merge_fields['prior'] = $prior;
        $prior--;
      }
      try {
        $status = db_merge('users_portfolio_'.$type)
            ->key(array('id' => is_int($id)?$id:null))
            ->fields(
                array_merge(
                    array_diff_key($element, array('responsibility'=>false,'coursework'=>false,'items'=>false)),
                    $merge_fields)
            )
            ->execute();
        if( $status == MergeQuery::STATUS_INSERT ) {
          $element['id'] = db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }else{
          $element['id'] = $id;
        }
        $return[$element['id']] = array_diff_key($element, array('responsibility'=>false,'coursework'=>false,'items'=>false));
        if(isset($date_tmp['start_year'])){
          $return[$element['id']]['start_year'] = $date_tmp['start_year'];
          $return[$element['id']]['start_mounth'] = $date_tmp['start_mounth'];
          $return[$element['id']]['end_year'] = $date_tmp['end_year'];
          $return[$element['id']]['end_mounth'] = $date_tmp['end_mounth'];
        }
        if(isset($element['responsibility']) && sizeof($element['responsibility'])
            && $this->getStatus()){
            $return[$element['id']]['responsibility'] = 
              $this->save_responsibility($type,$element); 
          }
        if(isset($element['coursework']) && sizeof($element['coursework'])
            && $this->getStatus()){
            $return[$element['id']]['coursework'] = 
              $this->save_responsibility($type,$element, 'coursework'); 
          }
        if(isset($element['items']) && sizeof($element['items'])
            && $this->getStatus()){
            $return[$element['id']]['items'] = 
              $this->save_responsibility($type,$element, 'items'); 
          }
        }
        
      catch (Exception $e) {
        $error = $e->errorInfo[2];
        $this->status[] =$error;
        drupal_set_message($error,'error');
      }
    }
    return $return;
  }
  
  private function save_custom($type,$data){
    var_dump($type,$data);
    die();
  }
  
  private function save_responsibility($type,$element, $field_name = 'responsibility'){
    $return = array();
    $status = true;
    if(isset($this->fields[$type]['data'][$element['id']][$field_name])){
      $return = $this->fields[$type]['data'][$element['id']][$field_name];
    }
    
    if(isset($element[$field_name]['new']) && sizeof($element[$field_name]['new'])){
      foreach($element[$field_name]['new'] as $i=>$new_responsibility){
        $element[$field_name]['n'.$i] = $new_responsibility;
      }
      unset($element[$field_name]['new']);
    }
    $prior = sizeof($element[$field_name]);
    foreach($element[$field_name] as $id=>$responsibility){
      
      if(isset($responsibility['start_year'])){
        $responsibility['year_start'] = $responsibility['start_year'];
        $responsibility['mounth_start'] = $responsibility['start_mounth'];
      }
      if(isset($responsibility['end_year']) && $responsibility['end_year']>0
          && isset($responsibility['end_mounth']) 
          && $responsibility['end_mounth']>=0){
        $responsibility['year_end'] = $responsibility['end_year'];
        $responsibility['mounth_end'] = $responsibility['end_mounth'];
      }elseif(isset($responsibility['start']) && (!isset($responsibility['end']) || $responsibility['end']== 0)){
        $responsibility['end'] = null;
      }
      if(isset($responsibility['start_year'])){
        $date_tmp = array(
            'start_year'=>$responsibility['start_year'],
            'start_mounth'=>$responsibility['start_mounth'],
            'end_year'=>$responsibility['end_year'],
            'end_mounth'=> $responsibility['end_mounth']
        );
      }
      unset($responsibility['start_year'],$responsibility['start_mounth'],
            $responsibility['end_year'],$responsibility['end_mounth']);
      $merge_fields = array('users_portfolio_'.$type.'_id'=>$element['id']);
      if($type == 'custom' && $field_name == 'items' && is_int($id)){
        $merge_fields['prior'] = $prior;
        $prior--;
      }      
      try {
        $status = db_merge('users_portfolio_'.$type.'_'.$field_name)
            ->key(array('id' => is_int($id)?$id:null))
            ->fields(
                array_merge(
                    $responsibility,
                    $merge_fields
                )
            )
            ->execute();
        if( $status == MergeQuery::STATUS_INSERT ) {
          $id = 
            db_query("SELECT LAST_INSERT_ID()")->fetchField();
        }
        if(isset($date_tmp['start_year'])){
          $return[$id]['start_year'] = $date_tmp['start_year'];
          $return[$id]['start_mounth'] = $date_tmp['start_mounth'];
          $return[$id]['end_year'] = $date_tmp['end_year'];
          $return[$id]['end_mounth'] = $date_tmp['end_mounth'];
        }
        $return[$id] = $responsibility;
      }
      catch (Exception $e) {
        $error =$e->errorInfo[2];
        $this->status[] =$error;
        drupal_set_message($error,'error');
      }
    }
    return $return;
  }
  
  /**
   * Helper to validate field
   *
   * $rule array
   * $field string
   * $data array
   * 
   * @return booalean
   */
  private function check($rule,$pfield,$field,$data,$type,$pid = false,$pnew = false,$id = false,$new = false){
    if($field == 'id' || $field == 'data'){
      return false;
    }
    if(!$this->check_required($rule,$pfield,$field,$data,$type,$pid,$pnew,$id,$new)){
      return false;
    }
    if(!$this->check_maxlength($rule,$pfield,$field,$data,$type,$pid,$pnew,$id,$new)){
      return false;
    }
    if(!$this->check_filter($rule,$pfield,$field,$data,$type,$pid,$pnew,$id,$new)){
      return false;
    }
    return true;
  }
  
  private function check_responsibility($rules,$data,$type,$pid,$pnew=false,$field_name = 'responsibility'){
    foreach($rules as $field=>$rule){
      if(isset($data['new'])){
        foreach($data['new'] as $i=>$sdata){
          $this->check($rule,$field_name,$field,$sdata,$type,$pid,$pnew,$i,true);
        }
      }
      foreach($data as $id=>$sdata){
        if($id != 'new'){
          $this->check($rule,$field_name,$field,$sdata,$type,$pid,$pnew,$id);
        }
      }
    }
  }
  
  /**
   * Helper to validate field on required
   *
   * $rule array
   * $field string
   * $data array
   * 
   * @return booalean
   */
  private function check_required($rule,$pfield,$field,$data,$type,$pid=false,$pnew=false,$id=false,$new=false){
    if(isset($rule['required']) && $rule['required'] 
          && (!array_key_exists($field,$data) || (isset($data[$field]) && $data[$field] == ''))){
        $error = t('Field %field is required.',array('%field'=>$rule['title']));
        $this->status[] =$error;
        drupal_set_message($error,'error');
        $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
        return false;
    }
    return true;
  }
  
  /**
   * Helper to validate field on length
   *
   * $rule array
   * $field string
   * $data array
   * 
   * @return booalean
   */
  private function check_maxlength($rule,$pfield,$field,$data,$type,$pid=false,$pnew=false,$id=false,$new=false){
    if(isset($rule['maxlength']) && (int)$rule['maxlength'] > 0
          && array_key_exists($field,$data) 
          && strlen($data[$field]) > (int)$rule['maxlength']){
        $error = t('Data in %field field is to long. Max %max allowed.',
            array(
              '%field'=>$rule['title'],
              '%max'=>$rule['maxlength']
            ));
        $this->status[] =$error;
        drupal_set_message($error,'error');
        $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
        return false;
    }
    return true;
  }
  
  /**
   * Helper to validate field on email
   *
   * $rule array
   * $field string
   * $data array
   * 
   * @return booalean
   */
  private function check_filter($rule,$pfield,$field,$data,$type,$pid=false,$pnew=false,$id=false,$new=false){
    if(isset($rule['filter']) && array_key_exists($field,$data)){
      switch($rule['filter']){
        case 'email':
          if(!filter_var($data[$field], FILTER_VALIDATE_EMAIL)){
            $error = t('Field %field is not valid email.',array('%field'=>$rule['title']));
            $this->status[] =$error;
            drupal_set_message($error,'error');
            $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
            return false;
          }
          break;
        case 'integer':
          if((string)(int)$data[$field] != $data[$field]){
            $error = t('Field %field is not valid integer.',array('%field'=>$rule['title']));
            $this->status[] =$error;
            drupal_set_message($error,'error');
            $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
            return false;
          }
          break;
        case 'end_year':
          if((string)(int)$data[$field] != $data[$field]){
            $error = t('Field %field is not valid integer.',array('%field'=>$rule['title']));
            $this->status[] =$error;
            drupal_set_message($error,'error');
            $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
            return false;
          }elseif(
              $data[$field] > 0 && (!isset($data['currently_studying']) || $data['currently_studying'] == 0) && 
              (($field == 'end_year' && isset($data['start_year']) 
                && $data[$field]<$data['start_year'])
              || ($field == 'end' && isset($data['start']) 
                && $data[$field]<$data['start']))){
            $error = t('%type %field should be greater than Start Year.',array(
              '%type'=>ucfirst($type),
              '%field'=>$rule['title']
            ));
            $this->status[] =$error;
            drupal_set_message($error,'error');
            $this->setError($type,$pfield,$field,$pid,$pnew,$id,$new);
            return false;
          }
          break;
      }
    }
    return true;
  }
  
  public function getStatus(){
    return !sizeof($this->status);
  }
  
  private function setError($type,$pfield,$field,$pid=false,$pnew=false,$id=false,$new=false){
    if($pid !== false){
      if($id !== false){
        if($pnew !== false){
          $this->error[$type]['new'][$pid][$pfield]['new'][$id][$field] = 'error';
        }else{
          if($new!==false){
            $this->error[$type][$pid][$pfield]['new'][$id][$field] = 'error';
          }else{
            $this->error[$type][$pid][$pfield][$id][$field] = 'error';
          }
        }
      }else{
        if($pnew !== false){
          $this->error[$type]['new'][$pid][$field] = 'error';
        }else{
          $this->error[$type][$pid][$field] = 'error';
        }
      }
    }else{
      $this->error[$type][$field] = 'error';
    }
  }
  
  public function getError(){
    return $this->status;
  }
  
  public function __get($name){
    if($name == 'error') return $this->error;
    if(array_key_exists($name,$this->fields['general_data'])){
      if(!isset($this->fields['general_data']['data'])){
        return '';
      }
      return $this->fields['general_data']['data'][$name];
    }
    
    if($name !== 'general_data' && array_key_exists($name,$this->fields)){
      if(isset($this->fields[$name]['data'])){
        return $this->fields[$name]['data'];
      }else{
        return array();
      }
    }
      
    return false;
  }
  
  public function loadCVS($id = null,$without_blocks = false){
    $data = array();
    if(!is_null($id)){
      $resume = db_query('SELECT `name`, `notes`, `text`, `pages` '
                        . 'FROM `users_portfolio_saved`'
                        . 'WHERE `id`=:id AND `users_uid` = :uid', array(':id' => $id,':uid'=>$this->uid))->fetchAssoc();
      if(!is_array($resume) || !sizeof($resume)){
        $error = t('This CVS not exist');
        $this->status[] =$error;
        return false;
      }
    }else{
      return $this->generateCVS();
    }
    
    if($without_blocks){
      return array(
        'id'=>$id,
        'name'=>$resume['name'],
        'notes'=>$resume['notes'],
        'pages'=>$resume['pages']
      );
    }
    
    return array(
      'id'=>$id,
      'name'=>$resume['name'],
      'notes'=>$resume['notes'],
      'text'=>$resume['text'],
      'pages'=>$resume['pages']
    );
  }
  
  private function generateCVS(){
    $data = '';
    $data .= '<h1 style="text-align:center;">'.$this->name.'</h1>';
    $data .= '<p style="text-align:center;"><small>'.$this->address.' | <a href="mailto:'.$this->emai.'">'.$this->email
        .'</a> | <span style="white-space:nowrap;">'.$this->cellphone.'</span></small></p>';
    $this->generateCVSEducation($data, $this->education);
    $this->generateCVSExperience($data, $this->experience);
    $this->generateCVSLeadership($data, $this->leadership);
    $this->generateCVSVolunteer($data, $this->volunteer);
    $this->generateCVSCustom($data, $this->custom);
    $this->generateCVSSkills($data, $this->skills);
 
    return array(
      'id'=>null,
      'name'=>t('Résumé Edit'),
      'notes'=>null,
      'text'=>$data
    );
  }

    /**
     * @param $data - data with mounth field
     * @return mixed
     */
  private function transformSeasons($data)
  {
    if (isset($data['start_mounth']) && $data['start_mounth'] > 12) {
      $data['start_mounth'] = getMonths($data['start_mounth']);
    }
    if (isset($data['end_mounth']) && $data['end_mounth'] > 12) {
      $data['end_mounth'] = getMonths($data['end_mounth']);
    }
    return $data;
  }

  /* nedd PHP 5.3+ */
  private function generateCVSEducation(&$return, $data){
    if(sizeof($data)){
      $return .= '<div><b>'.t('EDUCATION').'</b><hr/>';
      $return_string = '';
      foreach($data as $item){
        $item = $this->transformSeasons($item);
          $cityStr = implode(', ',array_filter(array(
              $item['city'],
              $item['state'],
              $item['country']
          )));
          $name = '<b>'.ucwords(strtolower($item['institution'])) . '</b>';
          if (!empty($item['course'])) {

              $name .= '<br/><i>'.$item['course'].'</i>';
          }
        $return_string .= '<table style="width:100%;"><tr><td>'.$name.'</td><td style="text-align:right">'.$cityStr;
          if (!empty($cityStr)) {
            $return_string .= '<br/>';
          }

          if($item['currently_studying'] ==1){
              $return_string .= t('Expected').' ';
              if (!empty($item['start_mounth']))
                  $return_string .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
              $return_string .= $item['start_year'];
          }else{
              if (!empty($item['start_mounth']))
                  $return_string .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
              $return_string .= $item['start_year'];
              if (empty($item['date_type'])) {
                  $return_string .= '-';
                  if (!empty($item['end_mounth']))
                      $return_string .= str_pad($item['end_mounth'], 2, 0, STR_PAD_LEFT).'/';
                  $return_string .= $item['end_year'];
              }
          }
          $return_string .= '</td></tr>';
        
        $afte_table_rows = array();
        $br_spr = '';
        if($item['major'] != '') {
          $afte_table_rows[] = '<i>Major GPA: </i>' . $item['major'];
          $br_spr = '<br/>';
        }
        if($item['minor'] != '') {
          $afte_table_rows[] = '<i>Minor(s): </i>' . $item['minor'];
          $br_spr = '<br/>';
        }
        if($item['cumulativegpa'] != '') {
          $afte_table_rows[] = '<i>Cumulative GPA: </i>' . $item['cumulativegpa'];
          $br_spr = '<br/>';
        }
        if($item['honors'] != ''){
          $afte_table_rows[] = '<i>'.t('Honors/Awards').'</i>: '.$item['honors'];
          $br_spr = '<br/>';
        }

        $afte_table_rows = implode('; ', $afte_table_rows);

        if(($item['major'] != '' || $item['cumulativegpa'] != ''  || $item['minor'] != '')
            && $item['honors'] != ''){
          $afte_table_rows .= '; ';
          $br_spr = '<br/>';
        }

        $return_coursework = array();
        if(isset($item['coursework'])){
          $item['coursework'] = array_filter($item['coursework'],function($coursework){return !empty($coursework['coursework']);});
          if(sizeof($item['coursework'])){
            foreach($item['coursework'] as $coursework){
                $return_coursework[] = '<li>' . $coursework['coursework'] . '</li>';
            }
          }
        }
          if (!empty($afte_table_rows)) {
              $return_string .= '<tr><td colspan="2"><i>'.$afte_table_rows.'</i></td></tr>';
          }
          $return_string .= '</table>';
          if (!empty($return_coursework)) {
              $return_string .= '<i>'.t('Coursework').': </i>';
              $return_string .= '<ul>' . implode('', $return_coursework) . '</ul>';
          }
      }
      $return .= $return_string.'</div>';
    }
  }
  
  private function generateCVSExperience(&$return, $data){
    if(sizeof($data)){
      $return .= '<div><b>'.t('EXPERIENCE').'</b><hr/>';
      $return_string = '';
      foreach($data as $item){
        $item = $this->transformSeasons($item);
        $return_string .= '<table style="width:100%;"><tr><td><b>'.$item['organization'].'</b></td><td style="text-align:right">'.
            implode(', ',array_filter(array(
              $item['city'],
              $item['state'],
              $item['country']
            ))).'</td></tr>';
        $return_string .= '<tr><td style="width:70%;"><i>'.$item['jobtitle'].'</i></td><td style="text-align:right">';

        if (!empty($item['start_mounth']))
          $return_string .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
        $return_string .= $item['start_year'];
        if($item['date_type'] == 0){
              $return_string .= '-';
              if($item['end_year'] > 0){
                  if (!empty($item['end_mounth']))
                    $return_string .= str_pad($item['end_mounth'], 2, 0, STR_PAD_LEFT).'/';
                    $return_string .= $item['end_year'];
              }else{
                  $return_string .= t('Present');
              }
        }
        $return_string .='</td></tr></table>';
        
        if(isset($item['responsibility']) && is_array($item['responsibility']) 
            && sizeof($item['responsibility'])){
          $return_string .= '<ul>';
          $return_responsibility = array();
          foreach($item['responsibility'] as $responsibility){
            $return_string .= '<li>'.implode('; ',array_filter(array(
              $responsibility['responsibility'],
              $responsibility['achievement']
            ))).'</li>';
          }
          $return_string .= '</ul>';
        }
      }
      $return .= $return_string.'</div>';
    }
  }
  
  private function generateCVSLeadership(&$return, $data){
    if(sizeof($data)){
      $return .= '<div><b>'.t('LEADERSHIP').'</b><hr/>';
      $return_string = '';
      foreach($data as $item){
        $item = $this->transformSeasons($item);
        $cityStr = implode(', ',array_filter(array(
            $item['city'],
            $item['state'],
            $item['country']
        )));
          $name = '<b>' . $item['organization'] . '</b>';
          if (!empty($item['designationtitle'])) {
              $name .= '<br/><i>'.$item['designationtitle'].'</i>';
          }
        $return_string .= '<table style="width:100%;"><tr><td>'.$name.'</td><td style="text-align:right">'.$cityStr;
        if (!empty($cityStr)) {
            $return_string .= '<br/>';
        }
          if (!empty($item['start_mounth']))
              $return_string .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
          $return_string .= $item['start_year'];
          if($item['date_type'] == 0){
              $return_string .= '-';
              if($item['end_year'] > 0){
                  if (!empty($item['end_mounth']))
                      $return_string .= str_pad($item['end_mounth'], 2, 0, STR_PAD_LEFT).'/';
                  $return_string .= $item['end_year'];
              }else{
                  $return_string .= t('Present');
              }
          }
        $return_string.='</td></tr>';
        $responsibilities_str = '';
        if((isset($item['responsibility']) && is_array($item['responsibility']) && sizeof($item['responsibility'])) ||
            !empty($item['details'])){
          $responsibilities = array();
          if (!empty($item['details'])) {
              $responsibilities[]= '<li>' . $item['details'] . '</li>';
          }
          if (!empty($item['responsibility'])) {
              foreach($item['responsibility'] as $responsibility){
                $responsibilities[]= '<li>' . $responsibility['more_details'] . '</li>';
              }
          }
          if (!empty($responsibilities)) {
            $responsibilities_str = '<ul>' . implode('',$responsibilities) . '</ul>';
          }
        }

          $return_string .='</table>';
          $return_string .= $responsibilities_str;

      }
      $return .= $return_string.'</div>';
    }
  }
  
  private function generateCVSVolunteer(&$return, $data){
      if(sizeof($data)){
          $return .= '<div><b>'.t('VOLUNTEER WORK').'</b><hr/>';
          $return_string = '';
          foreach($data as $item){
              $item = $this->transformSeasons($item);
              $cityStr = implode(', ',array_filter(array(
                  $item['city'],
                  $item['state'],
                  $item['country']
              )));
              $name = '<b>' . $item['organization'] . '</b>';
              if (!empty($item['designationtitle'])) {
                  $name .= '<br/><i>'.$item['designationtitle'].'</i>';
              }
              $return_string .= '<table style="width:100%;"><tr><td>'.$name.'</td><td style="text-align:right">'.$cityStr;
              if (!empty($cityStr)) {
                  $return_string .= '<br/>';
              }
              if (!empty($item['start_mounth']))
                  $return_string .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
              $return_string .= $item['start_year'];
              if($item['date_type'] == 0){
                  $return_string .= '-';
                  if($item['end_year'] > 0){
                      if (!empty($item['end_mounth']))
                          $return_string .= str_pad($item['end_mounth'], 2, 0, STR_PAD_LEFT).'/';
                      $return_string .= $item['end_year'];
                  }else{
                      $return_string .= t('Present');
                  }
              }
              $return_string.='</td></tr>';
              $responsibilities_str = '';
              if((isset($item['responsibility']) && is_array($item['responsibility']) && sizeof($item['responsibility'])) ||
                  !empty($item['description'])){
                  $responsibilities = array();
                  if (!empty($item['description'])) {
                      $responsibilities[]= '<li>' . $item['description'] . '</li>';
                  }
                  if (!empty($item['responsibility'])) {
                      foreach($item['responsibility'] as $responsibility){
                          $responsibilities[]= '<li>' . $responsibility['more_details'] . '</li>';
                      }
                  }
                  if (!empty($responsibilities)) {
                      $responsibilities_str = '<ul>' . implode('',$responsibilities) . '</ul>';
                  }
              }

              $return_string .='</table>';
              $return_string .= $responsibilities_str;

          }
          $return .= $return_string.'</div>';
      }
  }
  
  private function generateCVSCustom(&$return, $data){
    if(sizeof($data)){
      foreach($data as $section){
        if(isset($section['items'])){
          $return .= '<div><b>'.$section['title'].'</b><hr/>';
          $return_items = array();
          foreach($section['items'] as $i=>$item){
            $item = $this->transformSeasons($item);
            $return_items[$i] = '<table style="width:100%;"><tr><td><b>'.$item['title'].'</b></td><td style="text-align:right">';

            if (!empty($item['start_mounth']))
              $return_items[$i] .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
            $return_items[$i] .= $item['start_year'];
            if($item['date_type'] == 0){
              $return_items[$i] .= '-';
              if($item['end_year'] > 0){
                if (!empty($item['end_mounth']))
                  $return_items[$i] .= str_pad($item['start_mounth'], 2, 0, STR_PAD_LEFT).'/';
                $return_items[$i] .= $item['end_year'];
              }else{
                $return_items[$i] .= t('Present');
              }
            }
            
            $return_items[$i] .='</td></tr></table>';
            if(trim($item['description']) != ''){
              $return_items[$i] .= $item['description'];
            }
          }
          $return .= implode('<br/>',$return_items).'</div>';
        }
      }
    }
  }
  
  private function generateCVSSkills(&$return, $data){
    $br = '';
      $returnTmp = '<div><b>'.t('SKILLS	&	INTERESTS').'</b><hr/>';
      $skills_types = array(
        1=>t('Languages'),
        2=>t('Computer Skills'),
        3=>t('Interests'),
        4=>t('Awards'),
      );
      $langs = zportfolio_getLanguages();
      $langs_lvls = zportfolio_getLanguagesLevel();
      $skills_array = array();
      $return_array = array();
      foreach($data as $type=>$items){
        foreach($items as $item){
          if($type == 1){
            $skills_array[$type][$item['val1']] = '<b>'.
                (is_numeric($item['val1'])
                  ?$langs[$item['val1']]
                  :$item['val1']).'</b> '
                .$langs_lvls[$item['val2']];
            if($item['val3'] || $item['val4'] || $item['val5']){
              $skills_array[$type][$item['val1']] .= ' (';
              $skills_array[$type][$item['val1']] .= implode(',',array_filter(array(
                $item['val3']?t('Speak'):'',
                $item['val4']?t('Read'):'',
                $item['val5']?t('Write'):'',
              )));
              $skills_array[$type][$item['val1']] .= ')';
            }
          }else{
            $skills_array[$type][] = $item['val1'];
          }
        }
      }
      foreach($skills_array as $type=>$item){
        $return_array[] = "<i>{$skills_types[$type]}</i>: ".implode(', ',$item);
      }
      if(sizeof($return_array)){
        $br = '<br/>';
      }
      $returnTmp .= implode('<br/>',$return_array);
      if (trim($this->other) != '') {
          $returnTmp .= $br.'<i>'.t('Others').': </i>';
          $returnTmp .= $this->other;
      }
      $returnTmp .= '</div>';
      if (empty($return_array) && trim($this->other) == '') {
          $returnTmp = '';
      }
      $return .= $returnTmp;
  }
  
  public function saveCVS($id = null, $name = null, $data = null){
    if(is_string($name) && is_null($data)){
      $data = $name;
      $name = null;
    }
    if(!is_int($id)){
      if(is_string($id)){
        $name = $id;
      }
      $id = null;
    }    
    /**
    * Name can't be empty when creating new CVS
    */
    if(is_null($id) && (is_null($name) || trim($name) == '')){
      $error = t('Resume name is required.');
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    }
    
    $name = strip_tags($name);

    try {
      $status = db_merge('users_portfolio_saved')
          ->key(array('id' => is_int($id)?$id:null))
          ->fields(
              array_filter(array(
                'users_uid'=>$this->uid,
                'name'=>$name,
                'updated'=>is_int($id)?date('Y-m-d H:i:s'):null
              ))
          )
          ->execute();
      if( $status == MergeQuery::STATUS_INSERT ) {
        $id = db_query("SELECT LAST_INSERT_ID()")->fetchField();
      }else{
        $this->removeCVSFiles($id);
      }
      if(!is_null($data)){
        $this->saveCVSBlocks($id, $data);  
      }
    }
    catch (Exception $e) {
      $error = $e->errorInfo[2];
      $this->status[] =$error;
      drupal_set_message($error,'error');
    }
    
    return $id>0?(int)$id:false;
  }
  
  public function saveCVSNotes($id,$name,$note){
    if(trim($name) == ''){
      $error = t('Resume name is required.');
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    }
    $note = strip_tags($note);
    try {
      $status = db_merge('users_portfolio_saved')
          ->key(array('id' => is_int($id)?$id:null))
          ->fields(
              array(
                'users_uid'=>$this->uid,
                'name'=>$name,
                'notes'=>$note,
                'updated'=>is_int($id)?date('Y-m-d H:i:s'):null
              )
          )
          ->execute();
    }
    catch (Exception $e) {
      $error = $e->errorInfo[2];
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    }
    return true;
  }
  
  private function saveCVSBlocks($id, $text){
    
    if(!is_numeric($id)){
      $error = t('Datatype mismatch.');
      $this->status[] =$error;
      drupal_set_message($error,'error');
    }
    
    try {
      $status = db_merge('users_portfolio_saved')
          ->key(array('id' => $id))
          ->fields(
              array(
                'users_uid'=>$this->uid,
                'text'=>check_markup($text,'zportfolio_block') ,
                'updated'=>is_int($id)?date('Y-m-d H:i:s'):null
              )
          )
          ->execute();
    }
    catch (Exception $e) {
      $error = $e->errorInfo[2];
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    }
    return true;
  }
  
  public function zresumeFolder(){
    return DRUPAL_ROOT.'/'.variable_get('file_public_path', conf_path() . '/files/zresume/');
  }
  
  private function removeCVSFiles($id){
    $folder = $this->zresumeFolder();
    if(file_exists($folder.$id.'.pdf')) unlink($folder.$id.'.pdf');
    $files = glob($folder.$id.'_*');
    foreach($files as $f) {
        unlink($f);
    }
  }
  
  public function deleteCVS($id){
    try {
      db_delete('users_portfolio_saved')
      ->condition('id', $id)
      ->execute();
      $this->removeCVSFiles($id);
    }
    catch (Exception $e) {
      $error = $e->errorInfo[2];
      $this->status[] =$error;
      drupal_set_message($error,'error');
      return false;
    }
    return true;
  }
  
  public function getCVSList($limit = 30,$sort = false){
    $query = db_select('users_portfolio_saved', 'n')
      ->fields('n',array('id','name','notes','updated','created'))
      ->condition('users_uid', $this->uid)
      ->extend('PagerDefault')
      ->orderBy('if(updated IS NULL,created,updated)', 'DESC')
      ->orderBy('created', 'DESC')
      ->limit($limit);
    if($sort){
      $query->orderBy("n.id","DESC");
    }
      
    return $query->execute()
      ->fetchAll();
  }

  static function hasUserResume($uid)
  {
      return db_select('users_portfolio_saved', 'n')
          ->fields('n',array('id'))
          ->condition('users_uid', $uid)
          ->execute()
          ->rowCount();
  }
  
  public function generateDocument($id, $type = 'pdf',$download = true){
    $cvs = $this->loadCVS($id);
    if($cvs){
          $zresume_dir = $this->zresumeFolder();
          $pdf_file = "{$zresume_dir}{$id}.pdf";
          db_insert('users_portfolio_downloaded')
          ->fields(array(
              'user'=>$this->uid,
              'type'=>$type == 'pdf' ? 0 : 1,
              'portfolio'=>$id
          ))
          ->execute();
          if(file_exists($pdf_file)){
            switch($type){
              case 'pdf':
                $this->forceDownloadPDF($pdf_file,$cvs['name'].'.pdf',$download);
              break;
              case 'docx':
                $this->forceDownloadPDF("{$zresume_dir}{$id}".'.docx',$cvs['name'].'.docx',$download);
              break;
            }
            return;
          }
          module_load_include('php', 'zportfolio', 'libraries/mpdf/mpdf');
          $mpdf = new mPDF('','', 0, '', 9, 9, 16, 16, 9, 9, 'P');
          $stylesheet = file_get_contents(drupal_get_path('module', 'zportfolio') . '/css/pdf.css');
          $mpdf->WriteHTML($stylesheet,1);
          $mpdf->WriteHTML($cvs['text'],2);
          $mpdf->Output($pdf_file, 'F');
          chmod($pdf_file,0770);
          $p = 1;
          $pdf_pages_count = count($mpdf->pages);
          while($p <= $pdf_pages_count){
            $cmd = "gs -dNOPAUSE -dBATCH -dFirstPage=$p -dLastPage=$p -sDEVICE=png16m -r144 -dTextAlphaBits=4 -dGraphicsAlphaBits=4 -sOutputFile={$zresume_dir}{$id}_{$p}.png -f {$pdf_file}";
            exec($cmd);
            chmod("{$zresume_dir}{$id}_".$p++.".png",0770);
          }
          db_merge('users_portfolio_saved')
          ->key(array('id' => $id))
          ->fields(array('pages'=>$pdf_pages_count))
          ->execute();
          
          module_load_include('inc', 'zportfolio', 'libraries/phpdocx/classes/CreateDocx');
          $file_name = "{$zresume_dir}{$id}";
          $docx = new CreateDocx();
          $docx->modifyPageLayout('A4',array('marginTop'=>1200,'marginBottom'=>800, 'marginRight'=>500,'marginLeft'=>500));
          $html=$cvs['text'];
          $html = str_replace('><br></td>', '><font style="color:#FFF">-</font></td>', $html);
          $html = str_replace('</table><br>', '</table>', $html);
          $html = str_replace('<br><br>', '<p></p>', $html);
          $html = str_replace('</h1>', '</h1>', $html);
          $html = str_replace('<div', '<font class="sprt">&nbsp;</font><div', $html);
          $html = str_replace('<li>','<li> &#9679;  ',$html);
          $html = str_replace('<hr><table', '<hr><span style="font-size:1px;color:#fff;">---</span><table', $html);
          $html = str_replace('<table', '<table cellspacing="0" border="0"', $html);
          $html = str_replace('</table><font class="sprt">&nbsp;</font><div><br></div><i>','</table><p>&nbsp;</p><i>',$html);
          $html = '<style>'.file_get_contents(drupal_get_path('module', 'zportfolio') . '/css/docx.css').'</style>'.$html;
          $wordStyles = array('<p>' => 'NoSpacingPHPDOCX','<table>'=>'PlainTablePHPDOCX');
          $docx->embedHTML($html,array('parseDivs'=>'paragraph', 'wordStyles' => $wordStyles));
          $docx->createDocx($file_name); 
          chmod($file_name.'.docx',0777);
          switch($type){
            case 'pdf':
              $this->forceDownloadPDF($pdf_file,$cvs['name'].'.pdf',$download);
            break;
            case 'docx':
              $this->forceDownloadPDF("{$zresume_dir}{$id}".'.docx',$cvs['name'].'.docx',$download);
            break;
          }
    }
  }
  
  private function forceDownloadPDF($file,$name,$download){
      if(!$download){return;}
      header('Content-Description: File Transfer');
      header('Content-Type: application/octet-stream');
      header('Content-Disposition: attachment; filename="'.$name.'"');
      header('Content-Transfer-Encoding: binary');
      header('Connection: Keep-Alive');
      header('Expires: 0');
      header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
      header('Pragma: public');
      header('Content-Length: ' . filesize($file));
      readfile($file);
  }
  }
