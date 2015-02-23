<?php if (empty($js)): ?>
    <?php foreach ($items as $rid => $item): ?>
        <?php
            if(!empty($error['new']) && isset($item['new'])) {
                $error = $error['new'];
            }
        ?>
        <div class="row-fluid experience-responsibility experience-responsibility-<?php print $eid; ?> experience-<?php print $eid; ?>-responsibility-<?php print $rid; ?>" <?php print isset($item['new'])?'experience-responsibility-new':''; ?>"
             data-rid="<?php print $rid; ?>" data-eid="<?php print $eid; ?>">
            <div class="span6">
                <div class="small-icon icon-minus remove-experience-responsibility"></div>
                <textarea rows="1"
                          name="experience<?php print $new; ?>[<?php print $eid; ?>][responsibility]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $rid; ?>][responsibility]"
                          class="autowraps input-xlarge autowraps <?php print isset($error[$rid]['responsibility'])?'error':''; ?>" 
                          required spellcheck="true"><?php print $item['responsibility']; ?></textarea>
            </div>
            <div class="span6">
                <textarea rows="1"
                          name="experience<?php print $new; ?>[<?php print $eid; ?>][responsibility]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $rid; ?>][achievement]"
                          class="autowraps input-xlarge autowraps <?php print isset($error[$rid]['achievement'])?'error':''; ?>" 
                          spellcheck="true" ><?php print $item['achievement']; ?></textarea>
            </div>
        </div>
    <?php endforeach; ?>
<?php else: ?>
    <div class="row-fluid experience-responsibility experience-responsibility-<%= eid %> experience-responsibility-new experience-<%= eid %>-responsibility-<%= rid %>" data-rid="<%= rid %>"  data-eid="<%= eid %>">
        <div class="span6">
            <div class="small-icon icon-minus remove-experience-responsibility"></div>
            <textarea rows="1" name="experience<% if (isNew) {%>[new]<%} %>[<%= eid %>][responsibility][new][<%= rid %>][responsibility]"
                      class="autowraps input-xlarge autowraps" required spellcheck="true" ></textarea>
        </div>
        <div class="span6">
            <textarea rows="1" name="experience<% if (isNew) {%>[new]<%} %>[<%= eid %>][responsibility][new][<%= rid %>][achievement]"
                      class="autowraps input-xlarge autowraps" spellcheck="true"></textarea>
        </div>
    </div>
<?php endif; ?>