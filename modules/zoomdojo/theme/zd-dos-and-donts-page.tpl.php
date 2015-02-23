<div class="zd-dos-donts-list">
    <div class="job-search-tips-desc">
        <?php print $description; ?>
    </div>
    <?php foreach ($nodes as $item): ?>
    <div class="yp-block">
        <div>
            <a href="/<?php print $item->url; ?>">
                <h3>
                    <?php print $item->title; ?>
                </h3>
                <div>
                    <img src="<?php print $item->src; ?>" width="253" height="209" />
                </div>
            </a>
        </div>
        <span class="feature-shadow"></span>
    </div>
    <?php endforeach; ?>
</div>
