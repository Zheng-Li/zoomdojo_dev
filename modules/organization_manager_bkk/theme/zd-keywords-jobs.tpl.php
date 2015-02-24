<div class="featured-jobs-wrapper industries">
    <div class="featured-jobs-desc">
        If this works, I will change this content.
    </div>
    <?php if (!empty($results)): ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
        <?php foreach ($results as $result): ?>
            <a href="/<?php print $result->url; ?>">
                <div class="zd-one-industry">
                    <div class="industry-title">
                        <h3><?php print $result->title; ?></h3>
                    </div>
                    <div class="industry-img">
                        <img src="<?php print $result->image; ?>" alt="<?php print $result->title; ?>" width="242" height="138" />
                    </div>
                </div>
            </a>
        <?php endforeach; ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
    <?php endif; ?>
</div>