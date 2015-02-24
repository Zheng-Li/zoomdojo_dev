<form accept-charset="UTF-8" id="organization-manager-organization-edit" method="post" >
  <div>
    <input type="hidden" value="<?php print $organization->id; ?>" name="id">
    <div class="form-item form-type-textfield form-item-name">
      <label for="edit-name">
        Company Name
        <span title="This field is required." class="form-required">*</span>
      </label>
      <input type="text" class="form-text required" maxlength="255" size="60" value="<?php print $organization->name; ?>" name="name" id="edit-name">
    </div>
    <div class="form-item form-type-textarea form-item-description">
      <label for="edit-description">Description</label>
      <div class="form-textarea-wrapper resizable textarea-processed resizable-textarea">
        <textarea class="form-textarea" rows="5" cols="30" name="description" id="edit-description"><?php print $organization->description; ?></textarea>
      </div>
    </div>
    <fieldset id="edit-links-wrapper" class="form-wrapper collapse-processed">
      <legend>
        <span class="fieldset-legend">
            Links
          <span class="summary"></span>
        </span>
      </legend>
      <div class="form-item form-type-textfield form-item-home-link">
        <label for="edit-home-link">Career Page URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->homePageUrl; ?>" name="home_link" id="edit-home-link">
      </div>
      <div class="form-item form-type-textfield form-item-intern-link">
        <label for="edit-intern-link">Intern URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->internLink; ?>" name="intern_link" id="edit-intern-link">
      </div>
      <div class="form-item form-type-textfield form-item-graduate-link">
        <label for="edit-graduate-link">College Seniors / Recent Graduate URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->graduateLink; ?>" name="graduate_link" id="edit-graduate-link">
      </div>
      <div class="form-item form-type-textfield form-item-mba-link">
        <label for="edit-mba-link">MBA / Graduate+ URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->mbaLink; ?>" name="mba_link" id="edit-mba-link">
      </div>
      <div class="form-item form-type-textfield form-item-veteran-link">
        <label for="edit-veteran-link">Veterans URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->veteranLink; ?>" name="veteran_link" id="edit-veteran-link">
      </div>
      <!--div class="form-item form-type-textfield form-item-carrer-link">
        <label for="edit-carrer-link">Carrer URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->careerLink; ?>" name="carrer_link" id="edit-carrer-link">
      </div-->
      <div class="form-item form-type-textfield form-item-experienced-link">
        <label for="edit-experienced-link">Experienced Candidates URL:</label>
        <input type="text" class="form-text" maxlength="255" size="60" value="<?php print $organization->experiencedLink; ?>" name="experienced_link" id="edit-experienced-link">
      </div>
    </fieldset>
    <div class="form-item-float-left form-type-select form-item-industry-types">
      <label for="s2id_autogen1">Industry Types</label>
      <select id="edit-industry-types" name="industry_types[]" multiple="multiple" style="width:400px;" class="select2 form-select select2-offscreen" tabindex="-1">
        <?php foreach ($industry_types as $item): ?>
          <?php if (in_array($item->id, $orgIndustries)): ?>
            <option value="<?php print $item->id; ?>" selected="selected"><?php print $item->title; ?></option>
          <?php else: ?>
            <option value="<?php print $item->id; ?>"><?php print $item->title; ?></option>
          <?php endif; ?>
        <?php endforeach; ?>
      </select>
    </div>
    <div class="form-item form-type-select form-item-job-types">
      <label for="s2id_autogen2">Job Types</label>
      <select id="edit-job-types" name="job_types[]" multiple="multiple" style="width:400px;" class="select2 form-select select2-offscreen" tabindex="-1">
        <?php foreach ($job_types as $item): ?>
          <?php if (in_array($item->id, $orgTypes)): ?>
            <option value="<?php print $item->id; ?>" selected="selected"><?php print $item->title; ?></option>
          <?php else: ?>
            <option value="<?php print $item->id; ?>"><?php print $item->title; ?></option>
          <?php endif; ?>
        <?php endforeach; ?>
      </select>
    </div>
    <div class="clearfix"></div>
    <div id="all-global-location">
      <fieldset id="edit-gloc" class="form-wrapper collapse-processed">
        <legend>
          <span class="fieldset-legend">
              Locations
            <span class="summary"></span>
          </span>
        </legend>
        <div class="div-floar-right">
          <a class="button" id="add-new-location-row" href="#">Add location row</a>
        </div>
        <div id="insert-location-row">
          <?php if (!empty($locations)): ?>
            <?php foreach ($locations as $location): ?>
              <div class="fieldset-wrapper-row">
                <div class="form-type-select ">
                <label for="s2id_autogen2">Country</label>
                  <select id="edit-location-country" name="location[country][]" class="form-select edit-location-country">
                    <?php foreach ($countries as $item): ?>
                      <?php if ($item->id == $location->countryId): ?>
                        <option value="<?php print $item->id; ?>" selected="selected"><?php print $item->title; ?></option>
                      <?php else: ?>
                        <option value="<?php print $item->id; ?>"><?php print $item->title; ?></option>
                      <?php endif; ?>
                    <?php endforeach; ?>
                  </select>
                </div>
                <div class="form-type-select ">
                  <label for="s2id_autogen2">State </label>
                  <select id="edit-location-state" name="location[state][]" class="form-select edit-location-state">
                    <?php foreach (_ajax_organization_manager_getStatesOptions($location->countryId) as $item): ?>
                      <?php if ($item->id == $location->stateId): ?>
                        <option value="<?php print $item->id; ?>" selected="selected"><?php print $item->title; ?></option>
                      <?php else: ?>
                        <option value="<?php print $item->id; ?>"><?php print $item->title; ?></option>
                      <?php endif; ?>
                    <?php endforeach; ?>
                  </select>
                </div>
                <div class="form-type-select ">
                  <label for="s2id_autogen2">City</label>
                  <select id="edit-location-city" name="location[city][]" class="form-select edit-location-city">
                    <?php foreach (_ajax_organization_manager_getCitiesOptions($location->stateId) as $item): ?>
                      <?php if ($item->id == $location->cityId): ?>
                        <option value="<?php print $item->id; ?>" selected="selected"><?php print $item->title; ?></option>
                      <?php else: ?>
                        <option value="<?php print $item->id; ?>"><?php print $item->title; ?></option>
                      <?php endif; ?>
                    <?php endforeach; ?>
                  </select>
                </div>
                <div class="form-type-select ">
                  <div class="btn-delete"></div>
                </div>
                <div class="clearfix"></div>
              </div>
            <?php endforeach; ?>
          <?php else: ?>
            <div class="fieldset-wrapper-row">
              <div class="form-type-select ">
              <label for="s2id_autogen2">Country</label>
                <select id="edit-location-country" name="location[country][]" class="form-select edit-location-country">
                  <?php foreach ($countries as $item): ?>
                    <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
                  <?php endforeach; ?>
                </select>
              </div>
              <div class="form-type-select ">
                <label for="s2id_autogen2">State</label>
                <select id="edit-location-state" name="location[state][]" class="form-select edit-location-state">
                  <?php foreach ($states as $item): ?>
                    <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
                  <?php endforeach; ?>
                </select>
              </div>
              <div class="form-type-select ">
                <label for="s2id_autogen2">City</label>
                <select id="edit-location-city" name="location[city][]" class="form-select edit-location-city">
                  <?php foreach ($cities as $item): ?>
                    <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
                  <?php endforeach; ?>
                </select>
              </div>
              <div class="form-type-select ">
                <div class="btn-delete"></div>
              </div>
              <div class="clearfix"></div>
            </div>
          <?php endif; ?>
        </div>
        <div class="div-floar-right">
          <a class="button" id="add-new-location-row" href="#">Add location row</a>
	</div>
      </fieldset>
    </div>
    <div>
      <input type="submit" class="form-submit" value="save" name="op" id="edit-save">  
      <?php print $status_button; ?>
      <?php print $flag_delete_button; ?>
    </div>
  </div>
</form>

<script type="text/x-template" id="location-row-template">
  <div class="fieldset-wrapper-row">
    <div class="form-type-select ">
    <label for="s2id_autogen2">Country</label>
      <select id="edit-location-country" name="location[country][]" class="form-select edit-location-country">
        <?php foreach ($countries as $item): ?>
          <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
        <?php endforeach; ?>
      </select>
    </div>
    <div class="form-type-select ">
      <label for="s2id_autogen2">State</label>
      <select id="edit-location-state" name="location[state][]" class="form-select edit-location-state">
        <?php foreach ($states as $item): ?>
          <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
        <?php endforeach; ?>
      </select>
    </div>
    <div class="form-type-select ">
      <label for="s2id_autogen2">City</label>
      <select id="edit-location-city" name="location[city][]" class="form-select edit-location-city">
        <?php foreach ($cities as $item): ?>
          <option value="<?php print $item->id?>"><?php print $item->title; ?></option>
        <?php endforeach; ?>
      </select>
    </div>
    <div class="form-type-select ">
      <div class="btn-delete"></div>
    </div>
    <div class="clearfix"></div>
  </div>
</script>
