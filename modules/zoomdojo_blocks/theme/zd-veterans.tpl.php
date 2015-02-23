<div class="fr-veteran-blocks-wrapper">
    <?php if (!empty($description)): ?>
        <?php print $description; ?>
    <?php endif; ?>
    <?php if (!empty($blocks)): ?>
        <?php foreach ($blocks as $block): ?>
            <div class="col-lg-3" onclick="location.href='<?php print $block->url; ?>';">
                <div class="thumbnail">
                    <h2 class="fg-red"><?php print $block->title; ?></h2>
                    <img src="<?php print $block->image; ?>" alt="<?php print $block->title; ?>" width="253" height="180" />
                    <div class="caption">
                        <?php print $block->text; ?>
                    </div>
                </div>
            </div>
        <?php endforeach; ?>
    <?php endif; ?>
</div>