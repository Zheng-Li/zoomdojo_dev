<?php if (empty($js)): ?>
    <?php foreach ($items as $rid => $item): ?>
        <?php
        if(!empty($error['new']) && isset($item['new'])) {
            $error = $error['new'];
        }
        ?>
        <div class="row-fluid leadership-responsibility leadership-responsibility-<?php print $eid; ?>
        leadership-<?php print $eid; ?>-responsibility-<?php print $rid; ?> <?php print isset($item['new'])?'leadership-responsibility-new':''; ?>"
             data-rid="<?php print $rid; ?>" data-eid="<?php print $eid; ?>">
            <div class="span12">
                <div class="small-icon icon-minus remove-leadership-responsibility"></div>
                <textarea name="leadership<?php print $new; ?>[<?php print $eid; ?>][responsibility]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $rid; ?>][more_details]"
                          class="autowraps input-large textarea-large <?php print isset($error[$rid]['more_details'])?'error':''; ?>"
                          required spellcheck="true"><?php print $item['more_details']; ?></textarea>
            </div>
        </div>
    <?php endforeach; ?>
<?php else: ?>
    <div class="row-fluid leadership-responsibility leadership-responsibility-<%= eid %> leadership-responsibility-new leadership-<%= eid %>-responsibility-<%= rid %>" data-rid="<%= rid %>"  data-eid="<%= eid %>">
        <div class="span12">
            <div class="small-icon icon-minus remove-leadership-responsibility"></div>
            <textarea rows="1" name="leadership<% if (isNew) {%>[new]<%} %>[<%= eid %>][responsibility][new][<%= rid %>][more_details]"
                      class="autowraps input-large textarea-large" required spellcheck="true" ></textarea>
        </div>
    </div>
<?php endif; ?>