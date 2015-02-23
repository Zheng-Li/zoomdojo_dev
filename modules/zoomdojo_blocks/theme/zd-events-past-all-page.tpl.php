<div id="zd-events-view" class="zd-events-wrapper" data-url="/">
    <div class="zd-events-desc">
        <span class="back-block back-block-top-page">
            <div class="btn-back btn-back-top-page">
                <a href="javascript:history.go(-1)">Back</a>
            </div>
        </span>
    </div>
    <div id="zd-jobs-content">
        <?php if (!empty($events)): ?>
            <!-- PAGINATION -->
            <div class="container-fluid"  id="zd-events-content-body">
                <?php foreach ($events as $event): ?>
                    <div class="row-fluid one-event">
                        <div class="span12">
                            <div class="row-fluid">
                                <div class="span7 text-left">
                                    <h3>
                                        <a href="/<?php print $event->druUrl;?>">
                                            <?php print $event->title; ?>
                                        </a>
                                    </h3>
                                </div>
                                <div class="span5 text-right right-date">
                                    <?php print $event->dateStart; ?>
                                </div>
                            </div>
                            <div class="row-fluid">
                                <div class="span12 text-left event-description">
                                    <?php print $event->description; ?>
                                </div>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php else: ?>
            <div class="container-fluid"  id="zd-events-content-body">
                <div class="row-fluid">
                    <div class="span12 text-center">
                        <div class="alert alert-error">
                            <?php print t('No Events'); ?>
                        </div>
                    </div>
                </div>
            </div>
        <?php endif; ?>
    </div>
</div>
