<?php if (empty($js)): ?>
    <?php foreach ($items as $rid => $item): ?>
        <?php
        if(!empty($error['new']) && isset($item['new'])) {
            $error = $error['new'];
        }
        ?>
        <div class="row-fluid volunteer-responsibility volunteer-responsibility-<?php print $eid; ?>
        volunteer-<?php print $eid; ?>-responsibility-<?php print $rid; ?> <?php print isset($item['new'])?'volunteer-responsibility-new':''; ?>"
             data-rid="<?php print $rid; ?>" data-eid="<?php print $eid; ?>">
            <div class="span12">
                <div class="small-icon icon-minus remove-volunteer-responsibility"></div>
                <textarea name="volunteer<?php print $new; ?>[<?php print $eid; ?>][responsibility]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $rid; ?>][more_details]"
                          class="autowraps input-large textarea-large <?php print isset($error[$rid]['more_details'])?'error':''; ?>"
                          required spellcheck="true"><?php print $item['more_details']; ?></textarea>
            </div>
        </div>
    <?php endforeach; ?>
<?php else: ?>
    <div class="row-fluid volunteer-responsibility volunteer-responsibility-<%= eid %> volunteer-responsibility-new volunteer-<%= eid %>-responsibility-<%= rid %>" data-rid="<%= rid %>"  data-eid="<%= eid %>">
        <div class="span12">
            <div class="small-icon icon-minus remove-volunteer-responsibility"></div>
            <textarea rows="1" name="volunteer<% if (isNew) {%>[new]<%} %>[<%= eid %>][responsibility][new][<%= rid %>][more_details]"
                      class="autowraps input-large textarea-large" required spellcheck="true" ></textarea>
        </div>
    </div>
<?php endif; ?>