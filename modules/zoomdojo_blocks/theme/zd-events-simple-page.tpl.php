<div id="zd-events-view" class="zd-events-wrapper" data-url="/">
    <div class="zd-events-desc">
        Check out past Zoomdojo events and put future events onto your calendar. Network with industry professionals, and get perspectives on 21st century careers and where the jobs are. Build a community with other college students and young professionals.
    </div>
    <div class="container-fluid" id="past-upcoming-events">
        <div class="row-fluid">
            <div class="span12">
                <h2><?php print t('Upcoming Events'); ?></h2>
                <?php if (!empty($rightEvents)): ?>
                    <ul>
                        <?php foreach ($rightEvents as $event): ?>
                            <li>
                                <a href="<?php print $event->druUrl; ?>">
                                    <?php print $event->title; ?>: <span class="date-start"><?php print $event->dateStart; ?></span>
                                </a>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php else: ?>
                    <div class="no-upcoming-events"><?php print t('No events planned yet. Check back later.'); ?></div>
                <?php endif; ?>
            </div>
        </div>
    </div>
    <div id="zd-jobs-content">
        <h2><?php print t('Past Events'); ?></h2>
        <?php if (!empty($leftEvents)): ?>
            <ul>
                <?php foreach ($leftEvents as $event): ?>
                    <li>
                        <a href="<?php print $event->druUrl; ?>">
                            <?php print $event->title; ?>: <span class="date-start"><?php print $event->dateStart; ?></span>
                        </a>
                    </li>
                <?php endforeach; ?>
            </ul>
            <div class="text-right">
                <a href="/all-past-events"><?php print t('Read more...'); ?></a>
            </div>
        <?php else: ?>
            <div class="no-past-events"><?php print t('No past events.'); ?></div>
        <?php endif; ?>
    </div>
</div>
