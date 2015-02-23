<div class="zd-acc-wrapper">
    <?php if (!empty($items)): ?>
        <div class="accordion" id="zd-city-sblock">

        <?php foreach ($items as $cid => $category): ?>
            <div class="accordion-group">
                <div class="accordion-heading">
                    <a href="#<?php print $cid; ?>" data-toggle="collapse" data-parent="#zd-city-sblock" class="collapsed accordion-toggle" title="<?php print $category['title']; ?>">
                        <?php print $category['title']; ?>
                    </a>
                </div>
                <div id="<?php print $cid; ?>" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <ul>
                            <?php foreach ($category['data'] as $item): ?>
                                <li>
                                    <a href="<?php print $item->url; ?>" data-nw="<?php print $item->nw; ?>" class="zd-url">
                                        <?php print $item->title; ?>
                                    </a>
                                </li>
                            <?php endforeach; ?>
                        </ul>
                    </div>
                </div>
            </div>
        <?php endforeach; ?>

        </div>

    <?php endif; ?>
</div>

