<div id="zd-events-view" class="zd-events-wrapper" data-url="/">
    <div class="zd-events-desc">
        Check out past Zoomdojo events and put future events onto your calendar. Network with industry professionals, and get perspectives on 21st century careers and where the jobs are. Build a community with other college students and young professionals.
    </div>
    <div class="container-fluid" id="past-upcoming-events">
        <div class="row-fluid">
            <div class="span6">
                <h2><?php print t('Past Events'); ?></h2>
                <?php if (!empty($leftEvents)): ?>
                    <ul>
                        <?php foreach ($leftEvents as $event): ?>
                            <li>
                                <a href="<?php print $event->druUrl; ?>">
                                    <?php print $event->title; ?> <span class="date-start">(<?php print $event->dateStart; ?>)</span>
                                </a>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php else: ?>
                    <div class="no-past-events"><?php print t('No past events.'); ?></div>
                <?php endif; ?>
            </div>
            <div class="span6">
                <h2><?php print t('Upcoming Events'); ?></h2>
                <?php if (!empty($rightEvents)): ?>
                    <ul>
                        <?php foreach ($rightEvents as $event): ?>
                            <li>
                                <a href="<?php print $event->druUrl; ?>">
                                    <?php print $event->title; ?> <span class="date-start">(<?php print $event->dateStart; ?>)</span>
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
        <!-- PAGINATION -->
        <div class="container-fluid">
            <div class="row-fluid pagin">
                <div class="span12 text-center" id="week-info-str">
                    <?php print $info; ?>
                </div>
            </div>
            <div class="row-fluid pagin">
                <div class="span12 text-center">
                    <a href="<?php print $url . $prevDay; ?>" data-date="<?php print $prevDay; ?>" class="btn btn-danger btn-pager btn-pager-prev">
                        <i class="icon-chevron-left icon-white"></i>
                        <?php print t('Prev'); ?>
                    </a>
                    <div class="input-append date">
                          <input class="data-picker-pagin" size="16" type="text" value="<?php print $date; ?>" readonly />
                          <span class="add-on"><i class="icon-calendar"></i></span>
                    </div>
                    <a href="<?php print $url . $nextDay; ?>" data-date="<?php print $nextDay; ?>" class="btn btn-danger btn-pager btn-pager-next">
                        <?php print t('Next'); ?>
                        <i class="icon-chevron-right icon-white"></i>
                    </a>
                </div>
            </div>
        </div>
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
                                    <?php print $event->dateStart; ?> - <?php print $event->dateEnd; ?>
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

<div id="zd-big-loading-image" align="center" class="loading-image hide">
    <img src="/<?php print $path; ?>/images/loading-zoom.gif" id="zd-load-big-img" alt="Loading...">
</div>

<script type="text/x-template" id="one-event-template">
    <div class="row-fluid one-event">
        <div class="span12">
            <div class="row-fluid">
                <div class="span7 text-left">
                    <h3>
                        <a href="/<%= druUrl %>">
                            <%= title %>
                        </a>
                    </h3>
                </div>
                <div class="span5 text-right right-date">
                    <%= dateStart %> - <%= dateEnd %>
                </div>
            </div>
            <div class="row-fluid">
                <div class="span12 text-left event-description">
                    <%= description %>
                </div>
            </div>
        </div>
    </div>
</script>

<script type="text/x-template" id="events-empty-tmp">
    <div class="row-fluid">
        <div class="span12 text-center">
            <div class="alert alert-error">
                <?php print t('No Events'); ?>
            </div>
        </div>
    </div>
</script>