<?php if (empty($js)): ?>
    <?php foreach ($items as $rid => $item): ?>
        <?php
            if(!empty($error['new']) && isset($item['new'])) {
                $error = $error['new'];
            }
        ?>
        <div class="row-fluid education-coursework education-coursework-<?php print $eid; ?> education-<?php print $eid; ?>-coursework-<?php print $rid; ?>" <?php print (isset($item['new']) && !is_null($item['new']))?'education-coursework-new123':''; ?>"
             data-rid="<?php print $rid; ?>" data-eid="<?php print $eid; ?>">
            <div class="span12">
                <div class="small-icon icon-minus remove-education-coursework"></div>
                <textarea rows="1" name="education<?php print $new; ?>[<?php print $eid; ?>][coursework]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $rid; ?>][coursework]"
                   class="autowraps input-xlarge <?php print isset($error[$rid]['coursework'])?'error':''; ?>" spellcheck="true" ><?php print $item['coursework']; ?></textarea>
            </div>
        </div>
    <?php endforeach; ?>
<?php else: ?>
    <div class="row-fluid education-coursework education-coursework-<%= eid %> education-coursework-new education-<%= eid %>-coursework-<%= rid %>" data-rid="<%= rid %>"  data-eid="<%= eid %>">
        <div class="span12">
            <div class="small-icon icon-minus remove-education-coursework"></div>
            <textarea rows="1" name="education<% if (isNew) {%>[new]<%} %>[<%= eid %>][coursework][new][<%= rid %>][coursework]"
                       class="autowraps input-xlarge" spellcheck="true" ></textarea>
        </div>
    </div>
<?php endif; ?>