<div id="zd-find-jobs-common-view" class="zd-find-jobs-wrapper" data-url="<?php print (!$featuredJobs)?'/find-jobs-get-positions':'/jobs-by-key-get-pos'; ?>">
    <?php if (!$featuredJobs): ?>
        <div class="custom-title">
            <div class="row-fluid">
                <!--<div class="span9 text-left">
                    <h1 id="custom-page-title" class="custom-title"><?php print t('Job Search Results'); ?></h1>
                </div>-->
               <!-- <div class="span3 text-right">
                    <a href="javascript: findNewJobsPopup();" class="btn btn-danger"><?php print t('New Job Search'); ?> <i class="icon-white icon-search"></i></a>
                </div>-->
            </div>
        </div>
        <!--<div class="front-tb-right">
        <form id="findJobsFormMini" action="/find-positions" method="get">
            <div class="row-fluid" style="position:relative; right:90px;">
                <input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off"  placeholder="<?php print $keywords; ?>" class="input-large span4 keywords-autocomplete" style="margin-left:71px;"/>
                <input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off"  placeholder="<?php print $location; ?>" class="input-large span4 location-autocomplete" style="margin-left:71px;" />
            </div><br>
        </form>
        <a class="btn btn-danger btn-small fr-search-btn" style="position:relative;right:-210px;" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Go</a>
    </div>-->

        

    <!--tings code-->
    <?php endif; ?>
    <div id="zd-filter-panel">
        <div class="container-fluid" style="height:80px;">
            <!--<div class="row-fluid">-->
            <div class="row-fluid">
                <div class="row-fluid">
                    <!--<div class="span3">-->
                        <div class="span12">
                            <form id="findJobsFormMini" action="/find-positions" method="get">
                                <input name="keywords" value="" id="employer-autocomplete" type="text" class="keywords-autocomplete" autocomplete="off" placeholder="Type any Keyword" style="margin-left:71px; width:252px; font-size: 12px !important;" required/>
                                <!--<input name="keywords" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type any keywords" class="input-large span4 keywords-autocomplete" style="margin-left:71px; height:20px; position:relative; top:8px;" required/>-->
                                <!--<input name="location" value="" id="employer-autocomplete" type="text" autocomplete="off" placeholder="Type location" class="input-large span4 location-autocomplete" style="margin-left:71px; position:relative; top:8px;"/>-->
                                <input name="location" value="" id="employer-autocomplete" type="text" class="location-autocomplete" autocomplete="off" placeholder="Type Location" style="margin-left:71px; width:252px; font-size: 12px !important;" />
                                <a class="btn btn-danger btn-medium fr-search-btn" href="#" style="position:relative;top:-5px;right:-30px;" onclick="jQuery('#findJobsFormMini').submit(); return false;">Search</a>
                            </form>
                        <div class="dispalay-ctl" style="position:relative;top:17px;">
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
                    <div class="span6 text-center pagination" style="position:relative;left:230px;top:-8px;">
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
                        <span class="text" style="position:relative; top:-8px; left:165px;"><?php print t('Jobs'); ?></span>
                        <?php
                            $startLimit = $limit * $currentPage + 1;
                            if (count($positions) == 0) {
                                $startLimit = 0;
                            }
                        ?>
                    
                        <span id="zd-limit-row" style="position:relative; top:-8px; left:165px;"><?php print $startLimit; ?></span> <span style="position:relative; top:-8px; left:165px;">-</span>
                        <?php $endLimit = $limit * $currentPage + $limit; ?>
                        <span id="zd-end-limit-row" style="position:relative; top:-8px; left:165px;"><?php print ($endLimit > $countRows)?$countRows:$endLimit; ?></span><span style="position:relative; top:-8px; left:165px;"> <?php print t('of'); ?></span>
                        <span id="zd-count-row" style="position:relative; top:-8px; left:165px;"><?php print $countRows; ?></span>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div id="zd-jobs-content">
        <?php if (!empty($positions)): ?>
            <div class="container-fluid"  id="zd-jobs-content-body">
                <?php foreach ($positions as $position): ?>
                    <div class="row-fluid job-one">
                        <div class="span12">
                            <div class="row-fluid">
                                <div class="span7 text-left">
                                    <h3><a href="<?php print $position->Url; ?>" target="_blank"><?php print $position->Title; ?></a></h3>
                                </div>
                                <div class="span5 text-right share-view">
                                    <!-- Share button begin -->
                                    <!--Deleted by ting-->
                                    <!-- Share button end -->
                                    <!--Save button deleted here-->
                                </div>
                            </div>
                                <div class="org-meta-desc">
                                    <span><?php print $position->Name; ?></span>
                                    <span> | </span>
                                    <span><?php print $position->location; ?></span>
                                </div>
                                <br>
                            <div class="row-fluid">
                                <div class="span12 text-left">
                                    <div class="org-meta-desc">
                                        <?php if (!empty($position->Snippet)): ?>
                                            <?php print $position->Snippet; ?>
                                        <?php else: ?>
                                            <?php print t('Please click on job name for more info'); ?>
                                        <?php endif; ?>

                                    </div>
                           
                                    <div class="span12 text-center">
                                        <div class="org-meta-desc">
                                            Posted <?php print $position->post ?> ago
                                        </div>
                                    </div>
                                </div>
                            </div>
                            <div class="row-fluid">
                                <div class="span12 text-center">
                                    <div class="zd-first zd-hide collapse organization-job-content" id="organization-job-content-<?php print $position->ID; ?>"></div>
                                </div>
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
                <div class="span12 text-center pagination" style="position:relative;left:28px;">
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
                <h3><a href="<%= Url %>" target="_blank"><%= Title %></a></h3>
            </div>
            <div class="span5 text-right share-view">
            </div>
        </div>
            <div class="org-meta-desc">
                <span><%= Name %></span>
                <span> | </span>
                <span><%= location %></span>
            </div>
        <div class="row-fluid">
            <div class="span12 text-left">
                <div class="org-meta-desc">
                    <% if (Snippet != null) { %>
                            <%= Snippet %>
                        <% } else { %>
                            <?php print t('Please click on organisation name for more info'); ?>
                        <% } %>
                </div>

                <div class="org-meta-desc">
                        Post <%=post %> ago
                </div>
            </div>
        </div>
        <div class="row-fluid">
            <div class="span12 text-center">
                <div class="zd-first zd-hide collapse organization-job-content" id="organization-job-content-<%= ID %>"></div>
            </div>
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
