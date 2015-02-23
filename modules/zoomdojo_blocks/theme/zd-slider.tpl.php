<div class="fr-blocks">
    <?php if (!empty($blocks)): ?>
        <?php foreach ($blocks as $block): ?>
            <div class="col-lg-3" onclick="location.href='<?php print $block->url; ?>';">
                <div class="thumbnail">
                    <h3 class="fg-red"><?php print $block->title; ?></h3>
                    <img src="<?php print $block->image; ?>" alt="<?php print $block->title; ?>" width="346" height="187" />
                    <div class="caption">
                        <?php print $block->text; ?>
                    </div>
                </div>
            </div>
        <?php endforeach; ?>
    <?php endif; ?>
</div>