<div class="zd-items-wrapper">
    <?php if (!empty($items)): ?>
        <?php $c = 0; ?>
        <?php foreach ($items as $cid => $category): ?>
        <?php $hc = 0; ?>
        <div class="<?php print ($c++%2==1) ? 'dont' : 'do'; ?>">
            <h1><?php print $category['title']; ?></h1>
            <div>
                <ul>
                    <div class="show-items">
                        <?php for ($i = 0; $i < count($category['data']); $i++): ?>
                            <li>
                                <strong><?php print $category['begin_word']; ?></strong> <?php print $category['data'][$i]; ?>
                            </li>
                            <?php if (($category['num_show']) == $i) { $hc = 1; } ?>
                            <?php if (($category['num_show']-1) == $i): ?>
                                </div>
                                <div class="hide-items" id="zd-toogle-items-<?php print $cid; ?>">
                            <?php endif;?>
                        <?php endfor; ?>
                    </div>
					<?php if ($hc == 1): ?>
					    <div class="zd-toogle-items" data-cid="<?php print $cid; ?>"><span><?php print t('Read More'); ?></span></div>
					<?php endif;?>
                </ul>
            </div>
        </div>
		<?php endforeach; ?>
    <?php endif; ?>
</div>