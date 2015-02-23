<div class="one-event-wrapper container-fluid">
    <?php if ($detail): ?>
        <div class="row-fluid">
            <div class="span12">
                <?php print $widgetContent; ?>
            </div>
        </div>
    <?php else: ?>
        <div class="row-fluid">
            <div class="span6">
                <?php if ($event->upcoming): ?>
                    <?php if ($them): ?>
                        <a href="<?php print $event->url; ?>" class="btn btn-danger" target="_blank">
                            <?php print t('More info'); ?>
                            <i class="icon-info-sign icon-white"></i>
                        </a>
                        <a href="/<?php print $event->druUrl; ?>/detail" class="btn btn-danger">
                            <?php print t('Buy ticket'); ?>
                            <i class="icon-tag icon-white"></i>
                        </a>
                    <?php else: ?>
                        <a href="<?php print $event->url; ?>" class="btn btn-danger" target="_blank">
                            <?php print t('More info'); ?>
                            <i class="icon-info-sign icon-white"></i>
                        </a>
                    <?php endif; ?>
                <?php else: ?>
                    <?php if (!$event->old): ?>
                        <?php print t('Check back later for details'); ?>
                    <?php endif; ?>
                <?php endif; ?>
            </div>
            <div class="span6">
                <?php print $event->dateStart; ?>
            </div>
        </div>
        <div class="row-fluid">
            <div class="span12">
                <?php print $event->description; ?>
            </div>
        </div>
    <?php endif; ?>
</div>