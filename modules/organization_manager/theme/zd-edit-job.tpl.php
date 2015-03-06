<form accept-charset="UTF-8" id="organization-manager-job-edit" method="post" >
	<div>
		<fieldset id="organization-info-wrapper" class="form-wrapper collapse-processed">
			<legend>
        		<span class="fieldset-legend">
            		Organization Info
          		<span class="summary"></span>
        		</span>
      		</legend>
          <input id="org_id" type="hidden" value="<?php print $org_id; ?>" name="org-id">
    		<div style="float:left;margin-right:10px;padding:15px;width:15%;">
       			<label for="org_name">Organization Name</label>
        		<textarea id="org_name" type="text" rows="1" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;width:100%;resize:none;" 
            name="org-name" placeholder="e.g. Apple Inc..." readonly><?php print $org_name; ?></textarea>
    		</div>
    		<div style="float:left;margin-right:10px;padding:15px;width:30%;">
       			<label for="org_url">Organization Url</label>
        		<textarea id="org_url" type="text" rows="1" cols ="50" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;width:100%;resize:none;" 
            name="org-url" placeholder="http://www.example.com" readonly><?php print $org_url; ?></textarea>
    		</div>
        <div style="float:left;padding:15px;width:30%;">
            <label for="org_tags">Organization Tags</label>
            <textarea id="org_tags" type="text" rows="1" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;width:100%;resize:none;" 
            name="org-tags" placeholder="Tags go here...(Maxium 5 tags per organization)" readonly><?php print $org_tags; ?></textarea>
        </div>
		</fieldset>
		<fieldset id="edit-job-wrapper" class="form-wrapper collapse-processed">
			<legend>
        	<span class="fieldset-legend">
           		Job Info
          <span class="summary"></span>
        	</span>
      	</legend>
        <input id="job_id" value="<?php print $job_id; ?>" type="hidden" name="job-id">
      	<div style="float:left;padding:15px;margin-right:15px;">
    			<label for="job_title">Job Title</label>
    			<input id="job_title" value="<?php print $job_title; ?>" type="text" style="border:1px solid #ccc;font-size:17px;" name="job-title" 
          placeholder="e.g. Hiring Manager...">
    		</div>
      	<div style="float:left;padding:15px;">
      		<label for="job_tags">Job Tags</label>
      		<textarea id="job_tags" type="text" style="border:1px solid #ccc;font-size:17px;width:100%;resize:none;" rows="1" cols="50" name="job-tags" 
          placeholder="e.g. Internship, Software, Experienced..."><?php print $job_tags; ?></textarea>
      	</div>
        <div style="float:left;padding:15px;">
          <label for="weight">Job Weight</label>
          <select id="weight" name="job-weight" style="border:1px solid #ccc;font-size:17px;">
            <option value="1" <?php if($weight==1) print "selected"; ?>>Top sponsored job</option>
            <option value="0" <?php if($weight==0) print "selected"; ?>>None</option>
            <option value="-1" <?php if($weight==-1) print "selected"; ?>>Bottom sponsored job</option>
          </select>
          <!-- <input id="weight" value="<?php print $weight; ?>" type="text" style="border:1px solid #ccc;font-size:17px;" name="job-weight" placeholder="0"> -->
        </div>
      	<br style="clear:both;" />
      	<div style="float:left;padding:15px;margin-right:15px;">
      		<label for="job_url">Job URL</label>
      		<input id="job_url" value="<?php print $job_url; ?>" type="text" style="border:1px solid #ccc;font-size:17px;" maxlength="255" size="60" name="job-url" placeholder="e.g. http://www.abc.com">
      	</div>
        <div style="float:left;padding:15px;">
          <label for="url_status">Url Status</label>
          <input id="url_status" value="<?php print $job_url_status; ?>" type="text" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;" name="url-status" placeholder="e.g. 404" readonly>
        </div>
        <br style="clear:both;" />
      	<div style="float:left;margin-right:15px;padding:15px;">
      		<label for="date_created">Date Created</label>
      		<input id="date_created" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;" type="date" value="<?php print $date_created; ?>" name="date-created" readonly>
      	</div>
    		<div style="float:left;padding:15px;">
    			<label for="date_expired">Date Expired</label>
     			<input id="date_expired" style="border:1px solid #ccc;font-size:17px;" type="date" value="<?php print $date_expired; ?>" name="date-expired">
    		</div>
        <div style="float:left;padding:15px;">
          <label for="date_updated">Date Updated</label>
          <input id="date_updated" style="background-color:#EBEBE4;border:1px solid #ccc;font-size:17px;" type="date" value="<?php print $date_updated; ?>" name="date-updated" readonly>
        </div>
        <br style="clear:both;" />
        <div style="float:left;margin-right:15px;padding:15px;">
            <label for="city">City</label>
            <input id="city" type="text" value="<?php print $city; ?>" style="border:1px solid #ccc;font-size:17px;" name="city" placeholder="City of the job">
        </div>
        <div style="float:left;margin-right:15px;padding:15px;">
            <label for="state">State</label>
            <input id="state" type="text" value="<?php print $state; ?>" style="border:1px solid #ccc;font-size:17px;" name="state" placeholder="State of the job">
        </div>
        <div style="float:left;padding:15px;">
            <label for="country">Country</label>
            <input id="country" type="text" value="<?php print $country; ?>" style="border:1px solid #ccc;font-size:17px;" name="country" placeholder="Country of the job">
        </div>
     		<br style="clear:both;" />
    		<div style="padding:15px;">
     			<label for="job_snippet">Job Snippet</label>
     			<textarea id="job_snippet" style="border:1px solid #ccc;font-size:17px;" rows="3" cols="100" maxlength="500" type="text" name="job-snippet" placeholder="A brief Description of the job"><?php print $job_snippet; ?></textarea>
     		  <div id="character_count"></div>
        </div>
		</fieldset>
		<div>
          <input type="button" class="form-submit" value="Back to List" style="float:left;" onclick="history.go(-1);"/>
      		<input type="submit" class="form-submit" value="Save and Exit" name="op" id="edit-save" style="float:right;"/>  
      		<!-- <input type="submit" class="form-submit" value="Flag to Delete" name="op"/> -->
      </div>
	</div>
</form>