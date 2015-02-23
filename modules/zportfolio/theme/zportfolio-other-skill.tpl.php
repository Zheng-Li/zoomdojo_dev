<?php foreach ($items as $eid => $item): ?>
    <div class="other-skill skill-type-<?php print $type; ?> <?php print isset($item['new'])?'new-skill-other new-skill-other-'.$eid:''; ?>">
        <div class="small-icon icon-minus remove-skills-other" data-type="<?php print $type; ?>" data-eid="<?php print $eid; ?>"></div>
        <textarea rows="1" name="skills[<?php print $type; ?>]<?php print isset($item['new'])?'[new]':''; ?>[<?php print $eid; ?>][val1]"
                  class="autowraps" required spellcheck="true"><?php print $item['val1']; ?></textarea>
    </div>
<?php endforeach; ?>
