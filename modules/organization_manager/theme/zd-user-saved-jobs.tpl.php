<div id="zd-find-jobs-common-view" class="zd-my-saved-jobs-wrapper" data-url="/get-saved-jobs-data">
    <div id="zd-filter-panel">
        <div class="container-fluid">
            <div class="row-fluid">
                <div class="span8">
                    <h1><?php print t('My saved jobs'); ?></h1>
                </div>
                <div class="span4 text-right">
                    <span class="text"><?php print t('Jobs'); ?></span>
                    <?php
                        $startLimit = $limit * $currentPage + 1;
                        if (count($organizations) == 0) {
                            $startLimit = 0;
                        }
                    ?>
                    <span id="zd-limit-row"><?php print $startLimit; ?></span> -
                    <?php $endLimit = $limit * $currentPage + $limit; ?>
                    <span id="zd-end-limit-row"><?php print ($endLimit > $countRows)?$countRows:$endLimit; ?></span> <?php print t('of'); ?>
                    <span id="zd-count-row"><?php print $countRows; ?></span>
                </div>
            </div>
            <div class="row-fluid">
                <div class="span12 text-center pagination">
                    <?php if (!empty($countPage)): ?>
                        <?php if ($currentPage - 1 >= 0): ?>
                            <a href="<?php print $url; ?><?php print $currentPage - 1; ?>" data-page="<?php print $currentPage - 1; ?>"><?php print t('Prev'); ?></a>
                        <?php endif; ?>
                        <?php if (($currentPage - $dotted) > 0): ?>
                            <span class="dotted">...</span>
                        <?php endif; ?>
                        <?php for ($i = 0; $i < $countPage; $i++): ?>
                            <?php if ($i >= ($currentPage - $dotted) && $i <= ($currentPage + $dotted)): ?>
                                <?php if ($i == $currentPage): ?>
                                    <span><?php print $i+1; ?></span>
                                <?php else: ?>
                                    <a href="<?php print $url; ?><?php print $i; ?>" data-page="<?php print $i; ?>"><?php print $i+1; ?></a>
                                <?php endif; ?>
                            <?php endif; ?>
                        <?php endfor; ?>
                        <?php if (($currentPage + $dotted) < $countPage-1): ?>
                            <span class="dotted">...</span>
                        <?php endif; ?>
                        <?php if ($currentPage + 1 < $countPage): ?>
                            <a href="<?php print $url; ?><?php print $currentPage + 1; ?>" data-page="<?php print $currentPage + 1; ?>"><?php print t('Next'); ?></a>
                        <?php endif; ?>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>
    <div id="zd-jobs-content">
        <?php if (!empty($organizations)): ?>
            <div class="container-fluid"  id="zd-jobs-content-body">
                <?php foreach ($organizations as $job): ?>
                    <?php if ($job->status == 0): ?>
                    <div class="row-fluid job-one deleted">
                    <?php else: ?>
                    <div class="row-fluid job-one">
                    <?php endif; ?>
                        <div class="btn-delete" data-id="<?php print $job->id; ?>" data-type="1"></div>
                        <div class="span12">
                            <div class="row-fluid">
                                <div class="span7 text-left">
                                    <h3><a href="/<?php print $job->url; ?>" target="_blank"><?php print $job->title; ?></a></h3>
                                </div>
                                <div class="span5 text-right organization-name">
                                    <div>
                                        <a href="<?php print $job->orgUrl; ?>" target="_blank">
                                            <?php print $job->name; ?>
                                        </a>
                                    </div>
                                    <div class="share-view">
                                        <!-- Share button begin -->
                                        <a href="<?php print $home; ?>/<?php print $job->url; ?>" 
                                            class="btn btn-danger btn-share" 
                                            data-img="http://placehold.it/120x90&text=Logo"
                                            data-id="<?php print $job->id; ?>"
                                            data-title="ZoomDojo - cracking the Job Search Code for You"
                                            data-desc="Click here to see a job opportunity <?php print $job->title; ?>">
                                                <?php print t('Share'); ?>
                                            <i id="share-btn"></i>
                                        </a>
                                        <!-- Share button end -->
                                    </div>
                                </div>
                            </div>
                            <div class="row-fluid">
                                <div class="span12 text-left">
                                    <?php print $job->description; ?>
                                </div>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php else: ?>
            <div class="row-fluid">
                <div class="span12 text-center no-data">
                    <?php print t('No data'); ?>
                </div>
            </div>
        <?php endif; ?>
    </div>
    <div id="zd-find-jobs-footer">
        <div class="container-fluid">
            <div class="row-fluid">
                <div class="span12 text-center pagination">
                    <?php if (!empty($countPage)): ?>
                        <?php if ($currentPage - 1 >= 0): ?>
                            <a href="<?php print $url; ?><?php print $currentPage - 1; ?>" data-page="<?php print $currentPage - 1; ?>"><?php print t('Prev'); ?></a>
                        <?php endif; ?>
                        <?php if (($currentPage - $dotted) > 0): ?>
                            <span class="dotted">...</span>
                        <?php endif; ?>
                        <?php for ($i = 0; $i < $countPage; $i++): ?>
                            <?php if ($i >= ($currentPage - $dotted) && $i <= ($currentPage + $dotted)): ?>
                                <?php if ($i == $currentPage): ?>
                                    <span><?php print $i+1; ?></span>
                                <?php else: ?>
                                    <a href="<?php print $url; ?><?php print $i; ?>" data-page="<?php print $i; ?>"><?php print $i+1; ?></a>
                                <?php endif; ?>
                            <?php endif; ?>
                        <?php endfor; ?>
                        <?php if (($currentPage + $dotted) < $countPage-1): ?>
                            <span class="dotted">...</span>
                        <?php endif; ?>
                        <?php if ($currentPage + 1 < $countPage): ?>
                            <a href="<?php print $url; ?><?php print $currentPage + 1; ?>" data-page="<?php print $currentPage + 1; ?>"><?php print t('Next'); ?></a>
                        <?php endif; ?>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>
</div>

<?php if (empty($user->uid)): ?>
    <div id="sing-in-popup" class="modal hide fade in">
        <div class="modal-header">
            <button aria-hidden="true" data-dismiss="modal" class="close" type="button">×</button>
            <h3>
                <?php print t('Sing In'); ?> OR 
                <a href="/user/register" target="_blank"><?php print t('Sign Up'); ?></a>
            </h3>
        </div>
        <div class="modal-body">
            <?php print drupal_render(drupal_get_form("user_login")); ?>
        </div>
    </div>
<?php endif; ?>

<div id="zd-big-loading-image" align="center" class="loading-image hide">
    <img src="/<?php print $path; ?>/img/loading-zoom.gif" id="zd-load-big-img" alt="Loading...">
</div>

<script type="text/x-template" id="zd-loadding-little">
    <div id="zd-little-loading-image" align="center" class="loading-image">
        <img src="/<?php print $path; ?>/img/loading.gif" id="zd-load-little-img" alt="Loading...">
    </div>
</script>

<script type="text/x-template" id="one-organization-template">
    <% if (status == 0){ %>
    <div class="row-fluid job-one deleted">
    <% } else { %>
    <div class="row-fluid job-one">
    <% } %>
        <div class="btn-delete" data-id="<%= id %>" data-type="1"></div>
        <div class="span12">
            <div class="row-fluid">
                <div class="span7 text-left">
                    <h3><a href="/<%= url %>" target="_blank"><%= title %></a></h3>
                </div>
                <div class="span5 text-right organization-name">
                    <div>
                        <a href="<%= orgUrl %>" target="_blank">
                            <%= name %>
                        </a>
                    </div>
                    <div class="share-view">
                        <!-- Share button begin -->
                        <a href="<?php print $home; ?>/<%= url %>" 
                            class="btn btn-danger btn-share" 
                            data-img="http://placehold.it/120x90&text=Logo"
                            data-id="<%= id %>"
                            data-title="ZoomDojo - cracking the Job Search Code for You"
                            data-desc="Click here to see a job opportunity <%= title %>">
                                <?php print t('Share'); ?>
                                <i id="share-btn"></i>
                        </a>
                        <!-- Share button end -->
                    </div>
                </div>
            </div>
            <div class="row-fluid">
                <div class="span12 text-left">
                    <%= description %>
                </div>
            </div>
        </div>
    </div>
</script>

<script type="text/x-template" id="pagin-template">
    <% if (countPage != null) { %>
        <% if (currentPage - 1 >= 0) { %>
            <a href="<%= url %><%= currentPage - 1 %>" data-page="<%= currentPage - 1 %>"><?php print t('Prev'); ?></a>
        <% } %>
        <% if ((currentPage - dotted) > 0) { %>
            <span class="dotted">...</span>
        <% } %>
        <% for (i = 0; i < countPage; i++) { %>
            <% if (i >= (currentPage - dotted) && i <= (currentPage + dotted)) { %>
                <% if (i == currentPage) { %>
                    <span><%= i+1 %></span>
                <% } else { %>
                    <a href="<%= url %><%= i %>" data-page="<%= i %>"><%= i+1 %></a>
                <% } %>
            <% } %>
        <% } %>
        <% if ((currentPage + dotted) < countPage-1) { %>
            <span class="dotted">...</span>
        <% } %>
        <% if (currentPage + 1 < countPage) { %>
            <a href="<%= url %><%= currentPage + 1 %>" data-page="<%= currentPage + 1 %>"><?php print t('Next'); ?></a>
        <% } %>
    <% } %>
</script>

<script type="text/x-template" id="jobs-template">
    <div class="container-fluid">
        <div class="row-fluid">
            <% if ((currentPage-1) >= 0) { %>
                <div class="span1 text-center">
                    <div class="zd-jobs-pagination zd-arrow-left" data-page="<%= currentPage-1 %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location="<%= location %>"></div>
                </div>
            <% } %>
            <% if ((currentPage-1) >= 0 && (currentPage+1) < countPage) { %>
                <div class="span10 text-center">
            <% } else {%>
                <div class="span11 text-center">
            <% } %>
                <ul>
                    <% for (key in jobs) { %>
                        <li><a href="/job-details/<%= jobs[key].id %>" target="_blank"><%= jobs[key].title %></a></li>
                    <% } %>
                </ul>
                <div class="jobs-pagin">
                    <% for (i = 0; i < countPage; i++) { %>
                        <% if (i === currentPage) { %>
                            <span class="job-active-page img-circle"></span>
                        <% } else { %>
                            <span class="zd-jobs-pagination job-deactive-page img-circle img-polaroid" data-page="<%= i %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location="<%= location %>"></span>
                        <% } %>
                    <% } %>
                </div>
            </div>
            
            <% if ((currentPage+1) < countPage) { %>
                <div class="span1 text-center">
                    <div class="zd-jobs-pagination zd-arrow-right" data-page="<%= currentPage+1 %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location="<%= location %>"></div>
                </div>
            <% } %>
        </div>
    </div>
</script>