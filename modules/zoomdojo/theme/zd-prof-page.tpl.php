<div class="zd-young-prof-list">
    <div>
        <div class="yp-desc">
            <?php print $description; ?>
        </div>
        <hr>
    </div>
    <div class="zd-pager">
      <?php print $pager; ?>
    </div>
    <?php foreach ($terms as $item): ?>
        <div class="yp-block">
            <div>
                <a href="/<?php print $item->url; ?>">
                    <h3>
                        <?php print $item->name; ?>
                    </h3>
                    <div>
                        <img src="<?php print $item->src; ?>" width="253" height="144" />
                    </div>
                    <div class="yp-desk-inner">
                        <span><?php print $item->desc; ?><span>
                    </div>
                </a>
            </div>
            <span class="feature-shadow"></span>
        </div>
    <?php endforeach; ?>
    <div class="zd-pager">
      <?php print $pager; ?>
    </div>
</div>