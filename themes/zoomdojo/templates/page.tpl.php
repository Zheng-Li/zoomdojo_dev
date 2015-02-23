
    <div id="page-wrapper"><div id="page">



            <div id="header" class="<?php print $secondary_menu ? 'with-secondary-menu': 'without-secondary-menu'; ?>"><div class="section clearfix">



                    <?php if ($logo): ?>
                        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
                            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
                        </a>
                    <?php endif; ?>

                    <?php if ($site_name == $site_slogan): ?>
                        <div id="name-and-slogan"<?php if ($hide_site_name && $hide_site_slogan) { print ' class="element-invisible"'; } ?>>

                            <?php if ($site_name): ?>
                                <?php if ($title): ?>
                                    <div id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
                                        <strong>
                                            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                                        </strong>
                                    </div>
                                <?php else: /* Use h1 when the content title is empty */ ?>
                                    <h1 id="site-name"<?php if ($hide_site_name) { print ' class="element-invisible"'; } ?>>
                                        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
                                    </h1>
                                <?php endif; ?>
                            <?php endif; ?>

                            <?php if ($site_slogan): ?>
                                <div id="site-slogan"<?php if ($hide_site_slogan) { print ' class="element-invisible"'; } ?>>
                                    <?php print $site_slogan; ?>
                                </div>
                            <?php endif; ?>

                        </div> <!-- /#name-and-slogan -->
                    <?php endif; ?>



                    <?php if ($main_menu): ?>
                        <div id="main-menu" class="navigation navbar">

                            <div class="navbar-inner">
                                <div class="container">
                                    <button type="button" class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
                                        <span class="icon-bar"></span>
                                        <span class="icon-bar"></span>
                                        <span class="icon-bar"></span>
                                    </button>
                                    <div class="nav-collapse collapse">
                            <?php print theme('links__system_main_menu', array(
                                'links' => $main_menu,
                                'attributes' => array(
                                    'id' => 'main-menu-links',
                                    'class' => array('nav', 'navbar-nav'),
                                ),
                                'heading' => array(
                                    'text' => t('Main menu'),
                                    'level' => 'h2',
                                    'class' => array('element-invisible'),
                                ),
                            )); ?>


                            <?php print render($page['header']); ?>


                            <?php #if ($secondary_menu): ?>
                            <div id="secondary-menu" class="navigation dropdown">
                                <?php if (user_is_logged_in() == TRUE) { ?>
                                    <a href="#" class="greetings" data-toggle="dropdown">

                                        <?php	global $user;
                                        print "Welcome <b>" . organization_manager_user_getViewName() . "</b><i id=\"usericon-head\"></i>"; ?>

                                    </a>
                                    <ul class="dropdown-menu" id="user-m" role="menu" aria-labelledby="dLabel">
                                        <?php print theme('links__system_secondary_menu', array(
                                            'links' => $secondary_menu,
                                            'attributes' => array(
                                                'id' => 'secondary-menu-links',
                                                'class' => array('links', 'inline', 'clearfix'),
                                            ),
                                            'heading' => array(
                                                'text' => t('Secondary menu'),
                                                'level' => 'h2',
                                                'class' => array('element-invisible'),
                                            ),
                                        )); ?>
                                    </ul>



                                <?php }
                                else { ?>
                                    <div id="login-menu">
                                        <?php	$menu = menu_navigation_links('menu-login-menu');
                                        print theme('links__menu_main_page', array('links' => $menu)); ?>
                                    </div>
                                <?php };  ?>

                            </div> <!-- /#secondary-menu -->
                            <?php #endif; ?>



                                    </div>
                                </div>
                            </div>

                        </div> <!-- /#main-menu -->
                    <?php endif; ?>



                </div></div> <!-- /.section, /#header -->


            <!-- TOP BANNER BLOCK -->
            <div id="featured">
                <div class="section clearfix">
                    <?php if ($page['featured']): ?>
                        <?php print render($page['featured']); ?>
                    <?php endif; ?>
                </div>
            </div>
            <!-- TOP BANNER BLOCK -->

            <div id="main-wrapper" class="clearfix section">

                <?php if ($messages): ?>
                    <div id="messages"><div class="section clearfix alert fade in">
                            <a class="close" data-dismiss="alert" href="#">&times;</a>
                            <?php print $messages; ?>
                        </div></div> <!-- /.section, /#messages -->
                <?php endif; ?>

                <div id="main" class="clearfix <?php if ($page['sidebar_second']): ?> bg <?php endif; ?>">



                    <?php if ($breadcrumb): ?>
                        <div id="breadcrumb"><?php print $breadcrumb; ?></div>
                    <?php endif; ?>

                    <?php if ($page['sidebar_first']): ?>
                        <div id="sidebar-first" class="column sidebar"><div class="section">
                                <?php print render($page['sidebar_first']); ?>
                            </div></div> <!-- /.section, /#sidebar-first -->
                    <?php endif; ?>

                    <div id="content" class="column"><div class="section">
                            <?php #if ($page['highlighted']): ?><div id="highlighted"><?php #print render($page['highlighted']); ?></div><?php #endif; ?>
                            <a id="main-content"></a>
                            <?php print render($title_prefix); ?>
                            <?php if ($title): ?>
                                <h1 class="title" id="page-title">
                                    <?php print $title; ?>
                                </h1>
                            <?php endif; ?>
                            <?php print render($title_suffix); ?>
                            <?php if ($tabs): ?>
                                <div class="tabs">
                                    <?php print render($tabs); ?>
                                </div>
                            <?php endif; ?>
                            <?php print render($page['help']); ?>
                            <?php if ($action_links): ?>
                                <ul class="action-links">
                                    <?php print render($action_links); ?>
                                </ul>
                            <?php endif; ?>
                            <div class="<?php if ($page['sidebar_second']): ?> content-left <?php endif; ?>">
                                <?php print render($page['content']); ?>

                                <?php if ($page['sidebar_second']): ?><span class="back-block"><div class="btn-back"><a href="javascript:history.go(-1)">Back</a></div></span><?php endif; ?>
                            </div>
                            <?php #print $feed_icons; ?>

                        </div></div> <!-- /.section, /#content -->

                    <?php if ($page['sidebar_second']): ?>
                        <div id="sidebar-second" class="column sidebar"><div class="section">
                                <?php print render($page['sidebar_second']); ?>
                            </div></div> <!-- /.section, /#sidebar-second -->
                    <?php endif; ?>

                </div></div> <!-- /#main, /#main-wrapper -->

            <?php if ($page['triptych_first'] || $page['triptych_middle'] || $page['triptych_last']): ?>
                <div id="triptych-wrapper" class="section"><div id="triptych" class="clearfix">
                        <?php print render($page['triptych_first']); ?>
                        <?php print render($page['triptych_middle']); ?>
                        <?php print render($page['triptych_last']); ?>
                    </div></div> <!-- /#triptych, /#triptych-wrapper -->
            <?php endif; ?>

            <div id="footer-wrapper"><div class="section">

                    <?php if ($page['footer_firstcolumn'] || $page['footer_secondcolumn'] || $page['footer_thirdcolumn'] || $page['footer_fourthcolumn']): ?>
                        <div id="footer-columns" class="clearfix"><div class="columns">
                                <?php print render($page['footer_firstcolumn']); ?>
                                <?php print render($page['footer_secondcolumn']); ?>
                                <?php print render($page['footer_thirdcolumn']); ?>
                                <?php print render($page['footer_fourthcolumn']); ?>
                                <?php print render($page['footer_fifthcolumn']); ?>
                            </div>
                            <?php if ($page['footer_full_inside']): ?>
                                <?php print render($page['footer_full_inside']); ?>
                            <?php endif; ?>
                        </div> <!-- /#footer-columns -->
                    <?php endif; ?>

                    <?php if ($page['footer']): ?>
                        <div id="footer" class="clearfix">
                            <?php print render($page['footer']); ?>
                        </div> <!-- /#footer -->
                    <?php endif; ?>

                </div></div> <!-- /.section, /#footer-wrapper -->

        </div></div> <!-- /#page, /#page-wrapper -->


<?php if ($page['hidden']): ?>
    <?php print render($page['hidden']); ?>
<?php endif; ?>