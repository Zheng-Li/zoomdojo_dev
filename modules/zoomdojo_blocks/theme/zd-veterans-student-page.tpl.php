<div class="share-view">
    <?php
        $link = url($_GET['q'], array('absolute' => TRUE));
    ?>
    <!-- Share button begin -->
    <a href="<?php print $link; ?>"
       class="btn btn-danger btn-share"
       data-img=""
       data-title="Zoomdojo - Student Veterans (ZoomDojo - cracking the Job Search Code for You)"
       data-desc="I think that you will find this article interesting. <?php print organization_manager_user_getViewName();  ?>">
        <?php print t('Share'); ?>
        <i id="share-btn"></i>
    </a>
    <!-- Share button end -->
</div>
<div class="zd-tabs-wrapper">
    <div class="student-veterans-desc">
        <?php print t('Finished with high school and looking to make the transition back to college? Our curated list of colleges with available Veterans programs will offer the support that you need.'); ?>
        <br/><br/>
    </div>
    <?php if (!empty($items)): ?>
        <ul id="student-veterans-tab" class="nav nav-tabs">
            <?php foreach ($categories as $category): ?>
                <li>
                    <a href="#<?php print $category->id; ?>" data-toggle="tab"><?php print $category->title; ?></a>
                </li>
            <?php endforeach; ?>
        </ul>
        <div id="myTabContent" class="tab-content">
            <?php foreach ($categories as $category): ?>
                
                <div id="<?php print $category->id; ?>" class="fade tab-pane">
                    <table class="table table-striped">
                        <thead>
                            <tr>
                                <?php foreach ($category->fields as $field): ?>
                                    <th><?php print $field->name=='Url' && $category->id != 4?$category->title.' Website':$field->name; ?></th>
                                <?php endforeach; ?>
                            </tr>
                        </thead>
                        <tbody>
                            <?php foreach ($items[$category->id] as $item): ?>
                                <tr>
                                    <?php foreach ($category->fields as $k => $field): ?>
                                        <td>
                                            <?php if ($field->type === 'text'): ?>
                                                <?php $f = 'field'.$k; print $item->$f; ?>
                                            <?php elseif($field->type === 'link'): ?>
                                                <a href="<?php $f = 'field'.$k; print $item->$f; ?>">
                                                    <?php $f = 'field'.$k; print $item->$f; ?>
                                                </a>
                                            <?php endif; ?>
                                        </td>
                                    <?php endforeach; ?>
                                </tr>
                            <?php endforeach; ?>
                        </tbody>
                    </table>
                </div>

            <?php endforeach; ?>
        </div>
    <?php endif; ?>
</div>