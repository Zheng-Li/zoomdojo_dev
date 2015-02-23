<div class="front-top-block">
    <div class="front-tb-left">Quick Search for Jobs</div>
    <div class="front-tb-right">
        <form id="findJobsFormMini" action="/find-jobs" method="get">
            <div class="row-fluid">
                <select class="fullwidth check-choose" name="job_industry">
                    <option value="">The industry I am interested in is...</option>
                    <?php foreach($industryTypes as $key=>$val): ?>
                    <option value="<?php echo $key; ?>"><?php echo $val; ?></option>
                    <?php endforeach; ?>
                </select>
                <select class="fullwidth check-choose" name="job_type">
                    <option value="">I am looking at opportunities in...</option>
                    <option value="0">All jobs</option>
                    <?php foreach($jobTypes as $key=>$val): ?>
                    <option value="<?php echo $key; ?>"><?php echo $val; ?></option>
                    <?php endforeach; ?>
                </select>
                <select class="fullwidth" name="location[country]">
                    <?php foreach($locations as $val): ?>
                        <?php
                            if ($val->title == 'Global') {
                                $val->id = 0;
                            }
                        ?>
                        <option value="<?php echo $val->id; ?>"><?php echo $val->title; ?></option>
                    <?php endforeach; ?>
                </select>
            </div>
        </form>
        <a class="btn btn-danger btn-small fr-search-btn" href="#" onclick="jQuery('#findJobsFormMini').submit(); return false;">Go</a>
    </div>
</div>