<div id="zd-find-jobs-common-view" class="zd-find-jobs-wrapper" data-url="<?php print (!$featuredJobs)?'/find-jobs-get-organizations':'/featured-jobs-get-org'; ?>">
    <?php if (!$featuredJobs): ?>
        <div class="custom-title">
            <div class="row-fluid">
                <div class="span9 text-left">
                    <h1 id="custom-page-title" class="custom-title"><?php print t('Job Search Results'); ?></h1>
                </div>
                <div class="span3 text-right">
                    <a href="javascript: findNewJobsPopup();" class="btn btn-danger"><?php print t('New Job Search'); ?> <i class="icon-white icon-search"></i></a>
                </div>
            </div>
        </div>
    <?php endif; ?>
    <div id="zd-filter-panel">
        <div class="container-fluid">
            <div class="row-fluid">
                <?php if (!$featuredJobs): ?>
                    <div class="span4">
                        <span id="zd-location">
                            <?php print $allJobString; ?>
                        </span>
                    </div>
                    <div class="span8 text-right">
                        <div class="row-fluid">
                            <div class="span12">
                                <input type="text" id="search-keyword" class="typeahead"  placeholder="Find..." value="" />
                                <a href="#" class="btn btn-danger" id="btn-find-keyword"><i class="icon-white icon-search"></i></a>
                            </div>
                        </div>
                    </div>
                <?php else: ?>
                    <div class="span12">
                        <span id="zd-fj-location">
                            <?php print t('Internships in ').$industryStr; ?>
                        </span>
                    </div>
                <?php endif; ?>
            </div>
            <div class="row-fluid">
                <div class="row-fluid">
                    <div class="span3">
                        <div class="dispalay-ctl">
                            <span class="dispalay-text"><?php print t('Display by'); ?></span>
                            <select  id="dispalay-ctl"  class="dispalay-select input-mini">
                                <?php foreach ($displayArray as $row): ?>
                                    <?php if ($row == $limit): ?>
                                        <option value="<?php print $row; ?>" selected="selected"><?php print $row; ?></option>
                                    <?php else: ?>
                                        <option value="<?php print $row; ?>"><?php print $row; ?></option>
                                    <?php endif; ?>
                                <?php endforeach; ?>
                            </select>
                        </div>
                    </div>
                    <div class="span6 text-center pagination">
                        <?php if (!empty($countPage)): ?>
                            <?php if ($currentPage - 1 >= 0): ?>
                                <a href="<?php print $url; ?><?php print $currentPage - 1; ?>" class="prev-link" data-page="<?php print $currentPage - 1; ?>"><?php print t('Prev'); ?></a>
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
                                <a href="<?php print $url; ?><?php print $currentPage + 1; ?>" class="next-link" data-page="<?php print $currentPage + 1; ?>"><?php print t('Next'); ?></a>
                            <?php endif; ?>
                        <?php endif; ?>
                    </div>
                    <div class="span3">
                        <span class="text"><?php print t('Organizations'); ?></span>
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
            </div>
        </div>
    </div>
    <div id="zd-jobs-content">
        <?php if (!empty($organizations)): ?>
            <div class="container-fluid"  id="zd-jobs-content-body">
                <?php foreach ($organizations as $organization): ?>
                    <div class="row-fluid job-one">
                        <div class="span12">
                            <div class="row-fluid">
                                <div class="span7 text-left">
                                    <h3><a href="<?php print $organization->url; ?>" target="_blank"><?php print $organization->name; ?></a></h3>
                                </div>
                                <div class="span5 text-right share-view">
                                    <!-- Share button begin -->
                                    <a href="<?php print $home; ?>/find-jobs?keyword=1&job_type=<?php print $jobType; ?>&job_industry=<?php print $jobIndustry; ?>&location[country]=<?php print isset($location['country'])?$location['country']:0; ?>&location[state]=<?php print isset($location['state'])?$location['state']:0; ?>&location[city]=<?php print isset($location['city'])?$location['city']:0; ?>&company_name=<?php print $organization->encodeName; ?>"
                                        class="btn btn-danger btn-share" 
                                        data-img="http://placehold.it/120x90&text=Logo"
                                        data-id="<?php print $organization->id; ?>"
                                        data-title="Zoomdojo - Cracking the Job Search Code for You"
                                        data-desc="Click here to see a job opportunity in <?php print $organization->name; ?>.">
                                            <?php print t('Share'); ?>
                                        <i id="share-btn"></i>
                                    </a>
                                    <!-- Share button end -->
                                    <?php if($organization->saved): ?>
                                        <a href="#" class="btn btn-danger btn-save btn-saved" data-tooltips-text="<?php print t('Save this employer in your account for future reference'); ?>" data-id="<?php print $organization->id; ?>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Saved'); ?></span> <i id="save-btn"></i> </a>
                                    <?php else: ?>
                                        <a href="#" class="btn btn-danger btn-save tooltips" data-tooltips-text="<?php print t('Save this employer in your account for future reference'); ?>" data-id="<?php print $organization->id; ?>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Save'); ?></span> <i id="save-btn"></i> </a>
                                    <?php endif; ?>
                                    <?php if($userCanEdit): ?>
                                        <a href="/admin/organization-manager/organizations/edit/<?php print $organization->id; ?>" class="btn btn-danger" data-id="<?php print $organization->id; ?>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Edit'); ?></span> </a>
                                    <?php endif; ?>
                                </div>
                            </div>
                            <div class="row-fluid">
                                <div class="span12 text-left">
                                    <?php if (!empty($organization->metaTitle)): ?>
                                        <div class="org-meta-title">
                                            <?php print $organization->metaTitle; ?>.
                                        </div>
                                    <?php endif; ?>
                                    <div class="org-meta-desc">
                                        <?php if (!empty($organization->metaDesc)): ?>
                                            <?php print $organization->metaDesc; ?>
                                        <?php else: ?>
                                            <?php print t('Please click on organisation name for more info'); ?>
                                        <?php endif; ?>
                                    </div>
                                </div>
                            </div>
                            <div class="row-fluid">
                                <div class="span12 text-center">
                                    <div class="zd-first zd-hide collapse organization-job-content" id="organization-job-content-<?php print $organization->id; ?>"></div>
                                </div>
                            </div>
                        </div>
                        <div class="span12 text-center">
                            <div class="open-job" data-id="<?php print $organization->id; ?>" data-jtid="<?php print $jobType; ?>" data-count="<?php print $organization->jobsCount; ?>">
                                <div id="org-jobs-bottom-text-<?php print $organization->id; ?>">
                                    <span id="org-count-job-<?php print $organization->id; ?>"><?php print $organization->jobsCount; ?> </span>
                                    <?php print t('jobs offered'); ?>
                                </div>
                                <div class="zd-arrow zd-arrow-down" id="organization-job-icon-<?php print $organization->id; ?>"></div>
                            </div>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php else: ?>
            <div class="container-fluid"  id="zd-jobs-content-body">
                <div class="row-fluid">
                    <div class="span12 text-center">
                        <div class="alert alert-error">
                            <?php print t('No data'); ?>
                        </div>
                    </div>
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
                            <a href="<?php print $url; ?><?php print $currentPage - 1; ?>"  class="prev-link" data-page="<?php print $currentPage - 1; ?>"><?php print t('Prev'); ?></a>
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
                            <a href="<?php print $url; ?><?php print $currentPage + 1; ?>"  class="next-link" data-page="<?php print $currentPage + 1; ?>"><?php print t('Next'); ?></a>
                        <?php endif; ?>
                    <?php endif; ?>
                </div>
            </div>
        </div>
    </div>
</div>

<div id="zd-big-loading-image" align="center" class="loading-image hide">
    <img src="/<?php print $path; ?>/img/loading-zoom.gif" id="zd-load-big-img" alt="Loading...">
</div>

<script type="text/x-template" id="zd-loadding-little">
    <div id="zd-little-loading-image" align="center" class="loading-image">
        <img src="/<?php print $path; ?>/img/loading.gif" id="zd-load-little-img" alt="Loading...">
    </div>
</script>

<script type="text/x-template" id="one-organization-template">
    <div class="row-fluid job-one">
        <div class="span12">
            <div class="row-fluid">
                <div class="span7 text-left">
                    <h3><a href="<%= url %>" target="_blank"><%= name %></a></h3>
                </div>
                <div class="span5 text-right share-view">
                    <a href="<?php print $home; ?>/find-jobs?keyword=1&job_type=<%= opt.jobType %>&job_industry=<%= opt.jobIndustry %>&location[country]=<%= opt.location.country %>&location[state]=<%= opt.location.state %>&location[city]=<%= opt.location.city %>&company_name=<%= encodeName %>"
                        class="btn btn-danger btn-share" 
                        data-img="http://placehold.it/120x90&text=Logo"
                        data-id="<%= id %>"
                        data-title="Zoomdojo - Cracking the Job Search Code for You"
                        data-desc="click this link to see what opportunities for <%= opt.typeStr %> <%= name %> is offering in <%= opt.locationStr %>.">
                            <?php print t('Share'); ?>
                        <i id="share-btn"></i>
                    </a>
                    <% if(saved == 1) { %>
                        <a href="#" class="btn btn-danger btn-save btn-saved" data-tooltips-text="<?php print t('Save this employer in your account for future reference'); ?>" data-id="<%= id %>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Saved'); ?></span> <i id="save-btn"></i> </a>
                    <% } else { %>
                        <a href="#" class="btn btn-danger btn-save tooltips" data-tooltips-text="<?php print t('Save this employer in your account for future reference'); ?>" data-id="<%= id %>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Save'); ?></span> <i id="save-btn"></i> </a>
                    <% } %>
                    <?php if($userCanEdit): ?>
                        <a href="admin/organization-manager/organizations/edit/<%= id %>" class="btn btn-danger" data-id="<%= id %>" data-uid="<?php print $user->uid; ?>"><span class="saved-text-for-replace"><?php print t('Edit'); ?></span> </a>
                    <?php endif; ?>
                </div>
            </div>
            <div class="row-fluid">
                <div class="span12 text-left">
                    <% if (metaTitle != null){ %>
                        <div class="org-meta-title">
                            <%= metaTitle %>.
                        </div>
                    <% } %>
                    <div class="org-meta-desc">
                        <% if (metaDesc != null) { %>
                            <%= metaDesc %>
                        <% } else { %>
                            <?php print t('Please click on organisation name for more info'); ?>
                        <% } %>
                    </div>
                </div>
            </div>
            <div class="row-fluid">
                <div class="span12 text-center">
                    <div class="zd-first zd-hide collapse organization-job-content" id="organization-job-content-<%= id %>"></div>
                </div>
            </div>
        </div>
        <div class="span12 text-center">
            <div class="open-job" data-id="<%= id %>" data-jtid="<%= globalJobType %>" data-count="<%= jobsCount%>">
                <div id="org-jobs-bottom-text-<%= id %>">
                    <span id="org-count-job-<%= id %>"><%= jobsCount %></span>
                    <?php print t('jobs offered'); ?>
                </div>
                <div class="zd-arrow zd-arrow-down" id="organization-job-icon-<%= id %>"></div>
            </div>
        </div>
    </div>
</script>

<script type="text/x-template" id="pagin-template">
    <% if (countPage != null) { %>
        <% if (currentPage - 1 >= 0) { %>
            <a href="<%= url %><%= currentPage - 1 %>"  class="prev-link" data-page="<%= currentPage - 1 %>"><?php print t('Prev'); ?></a>
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
            <a href="<%= url %><%= currentPage + 1 %>"  class="next-link" data-page="<%= currentPage + 1 %>"><?php print t('Next'); ?></a>
        <% } %>
    <% } %>
</script>

<script type="text/x-template" id="jobs-template">
    <div class="container-fluid">
        <div class="row-fluid">
            <% if ((currentPage-1) >= 0) { %>
                <div class="span1 text-center">
                    <div class="zd-jobs-pagination zd-arrow-left" data-page="<%= currentPage-1 %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location-c="<%= location.country %>" data-location-s="<%= location.state %>" data-location-t="<%= location.city %>"></div>
                </div>
            <% } else {%>
                <div class="span0 text-center"></div>
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
                            <span class="zd-jobs-pagination job-deactive-page img-circle img-polaroid" data-page="<%= i %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location-c="<%= location.country %>" data-location-s="<%= location.state %>" data-location-t="<%= location.city %>"></span>
                        <% } %>
                    <% } %>
                </div>
            </div>
            
            <% if ((currentPage+1) < countPage) { %>
                <div class="span1 text-center">
                    <div class="zd-jobs-pagination zd-arrow-right" data-page="<%= currentPage+1 %>" data-jtid="<%= jobType %>" data-jiid="<%= jobIndustry %>" data-id="<%= organizationId %>" data-location-c="<%= location.country %>" data-location-s="<%= location.state %>" data-location-t="<%= location.city %>"></div>
                </div>
            <% } %>
        </div>
    </div>
</script>









