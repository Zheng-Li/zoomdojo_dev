<div class="zd-acc-wrapper">
    <?php if (!empty($item)): ?>
        <div class="accordion" id="zportfolio-single-tips">

            <div class="accordion-group">
                <div class="accordion-heading">
                    <a href="#zportfolio-single-tips-id" data-toggle="collapse" data-parent="#zportfolio-single-tips" class="collapsed accordion-toggle" title="<?php print $item['title']; ?>">
                        <?php print $item['title']; ?>
                    </a>
                </div>
                <div id="zportfolio-single-tips-id" class="accordion-body collapse">
                    <div class="accordion-inner">
                        <?php print $item['text']; ?>
                    </div>
                </div>
            </div>

        </div>

    <?php endif; ?>
</div>
