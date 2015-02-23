<div class="featured-jobs-wrapper industries">
    <div class="featured-jobs-desc">
        If this works, I will change this content.
    </div>
    <?php if (!empty($tagged_jobs)): ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
        <?php foreach ($tagged_jobs as $tagged_job): ?>
            <a href="/<?php print $tagged_job->url; ?>">
                <div class="zd-one-industry">
                    <div class="industry-title">
                        <h3><?php print $tagged_job->title; ?></h3>
                    </div>
                    <div class="industry-img">
                        <img src="<?php print $tagged_job->image; ?>" alt="<?php print $tagged_job->title; ?>" width="242" height="138" />
                    </div>
                </div>
            </a>
        <?php endforeach; ?>
        <div class="industries-pager">
            <?php print $pager; ?>
        </div>
    <?php endif; ?>
</div>